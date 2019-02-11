
#include "open_addressing_map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static uint32_t
p(uint32_t k, unsigned int i, unsigned int m)
{
    return (k + i) & (m - 1);
}

struct hash_table *empty_table(uint32_t size,
                               compare_func key_cmp,
                               destructor_func key_destructor,
                               destructor_func val_destructor)
{
    struct hash_table *table =
        (struct hash_table*)malloc(sizeof(struct hash_table));
    table->table =
        (struct bin *)malloc(size * sizeof(struct bin));
    struct bin *end = table->table + size;
    for (struct bin *bin = table->table; bin != end; ++bin) {
        bin->is_free = true;
        bin->is_deleted = false;
    }
    table->size = size;
    table->active = table->used = 0;
    table->key_cmp = key_cmp;
    table->key_destructor = key_destructor;
    table->val_destructor = val_destructor;
    return table;
}

void delete_table(struct hash_table *table)
{
    if (table->key_destructor || table->val_destructor) {
        struct bin *end = table->table + table->size;
        for (struct bin *bin = table->table; bin != end; ++bin) {
            if (bin->is_free || bin->is_deleted) continue;
            if (table->key_destructor)
                table->key_destructor(bin->key);
            if (table->val_destructor)
                table->val_destructor(bin->value);
        }
    }
    free(table->table);
    free(table);
}

static void resize(struct hash_table *table, uint32_t new_size)
{
    struct bin *old_bins = table->table;
    uint32_t old_size = table->size;

    table->table = (struct bin *)malloc(new_size * sizeof(struct bin));
    struct bin *end = table->table + new_size;
    for (struct bin *bin = table->table; bin != end; ++bin) {
        bin->is_free = true;
        bin->is_deleted = false;
    }
    table->size = new_size;
    table->active = table->used = 0;

    end = old_bins + old_size;
    for (struct bin *bin = old_bins; bin != end; ++bin) {
        if (bin->is_free || bin->is_deleted) continue;
        add_map(table, bin->hash_key, bin->key, bin->value);
    }

    free(old_bins);
}

void add_map(struct hash_table *table,
             uint32_t hash_key,
             void *key, void *value)
{
    uint32_t index;
    bool contains = (bool)lookup_key(table, hash_key, key);
    for (uint32_t i = 0; i < table->size; ++i) {
        index = p(hash_key, i, table->size);
        struct bin *bin = & table->table[index];

        if (bin->is_free) {
            bin->is_free = bin->is_deleted = false;
            bin->hash_key = hash_key;
            bin->key = key;
            bin->value = value;
            // we have one more active element
            // and one more unused cell changes character
            table->active++; table->used++;
            break;
        }

        if (bin->is_deleted && !contains) {
            bin->is_free = bin->is_deleted = false;
            bin->hash_key = hash_key;
            bin->key = key;
            bin->value = value;
            // we have one more active element
            // but we do not use more cells since the
            // deleted cell was already used.
            table->active++;
            break;
        }

        if (bin->hash_key == hash_key) {
            if (table->key_cmp(bin->key, key)) {
                delete_key(table, hash_key, key);
                add_map(table, hash_key, key, value);
                return; // Done
            } else {
                // we have found the key but with a
                // different value...
                continue;
            }
        }
    }

    if (table->used > table->size / 2)
        resize(table, table->size * 2);
}

void delete_key(struct hash_table *table,
                uint32_t hash_key, void *key)
{
    for (uint32_t i = 0; i < table->size; ++i) {
        uint32_t index = p(hash_key, i, table->size);
        struct bin *bin = & table->table[index];

        if (bin->is_free) return;

        if (!bin->is_deleted
            && bin->hash_key == hash_key
            && table->key_cmp(bin->key, key)) {
            bin->is_deleted = true;
            if (table->key_destructor)
                table->key_destructor(bin->key);
            if (table->val_destructor)
                table->val_destructor(bin->value);
            table->active--;
            break;
        }
    }

    if (table->active < table->size / 8)
        resize(table, table->size / 2);
}

void *lookup_key (struct hash_table *table,
                    uint32_t hash_key, void *key)
{
    for (uint32_t i = 0; i < table->size; ++i) {
        uint32_t index = p(hash_key, i, table->size);
        struct bin *bin = & table->table[index];

        if (bin->is_free)
            return 0;
        if (!bin->is_deleted
            && bin->hash_key == hash_key
            && table->key_cmp(bin->key, key))
            return bin->value;
    }
    return 0;
}

