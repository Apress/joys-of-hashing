
#include "hash.h"
#include <stdlib.h>
#include <string.h>

struct hash_table *empty_table(uint32_t size)
{
    struct hash_table *table =
        (struct hash_table*)malloc(sizeof(struct hash_table));
    table->table = (struct bin *)malloc(size * sizeof(struct bin));
    for (uint32_t i = 0; i < size; ++i) {
        struct bin *bin = & table->table[i];
        bin->is_free = true;
    }
    table->size = size;
    return table;
}

void delete_table(struct hash_table *table)
{
    free(table->table);
    free(table);
}

void insert_key(struct hash_table *table, uint32_t key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = key & mask; // or key % table->size;
    struct bin *bin = & table->table[index];
    if (bin->is_free) {
        bin->key = key;
        bin->is_free = false;
    } else {
        // There is already a key here, so we have a
        // collision. We cannot deal with this yet.
    }
}

bool contains_key(struct hash_table *table, uint32_t key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = key & mask; // or key % table->size;
    struct bin *bin = & table->table[index];
    if (!bin->is_free && bin->key == key) {
        return true;
    } else {
        return false;
    }
}

void delete_key(struct hash_table *table, uint32_t key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = key & mask; // or key % table->size;
    struct bin *bin = & table->table[index];
    if (bin->key == key) {
        bin->is_free = true;
    }
}
