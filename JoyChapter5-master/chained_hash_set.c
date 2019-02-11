
#include "chained_hash_set.h"
#include "linked_lists_set.h"
#include <stdlib.h>
#include <stdio.h>

static void resize(struct hash_table *table, uint32_t new_size)
{
    // Remember these...
    uint32_t old_size = table->size;
    struct linked_list **old_bins = table->table;

    // Set up the new table
    table->table =
        (struct linked_list **)malloc(new_size * sizeof(struct linked_list *));
    for (int i = 0; i < new_size; ++i) {
        table->table[i] = new_linked_list();
    }
    table->size = new_size;
    table->used = 0;

    // Copy keys
    for (int i = 0; i < old_size; ++i) {
        struct linked_list *list = old_bins[i];
        while ( (list = list->next) ) {
            insert_key(table, list->hash_key, list->key);
        }
    }

    // Delete old table but not the resources
    // (we have moved those)
    for (int i = 0; i < old_size; ++i) {
        delete_linked_list(old_bins[i], table->destructor, false);
    }
    free(old_bins);
}

struct hash_table *empty_table(uint32_t size,
                               compare_func cmp,
                               destructor_func destructor)
{
    struct hash_table *table =
        (struct hash_table *)malloc(sizeof(struct hash_table));
    table->table =
        (struct linked_list **)malloc(size * sizeof(struct linked_list *));
    for (int i = 0; i < size; ++i) {
        table->table[i] = new_linked_list();
    }
    table->size = size;
    table->used = 0;
    table->cmp = cmp;
    table->destructor = destructor;
    return table;
}

void delete_table(struct hash_table *table)
{
    for (int i = 0; i < table->size; ++i) {
        delete_linked_list(table->table[i], table->destructor, true);
    }
    free(table->table);
    free(table);
}

void insert_key(struct hash_table *table,
                uint32_t hash_key, void *key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = hash_key & mask;

    if (list_contains_key(table->table[index],
                           hash_key, key, table->cmp)) {
        list_delete_key(table->table[index],
                        hash_key, key,
                        table->cmp, table->destructor);
        list_insert_key(table->table[index],
                        hash_key, key, table->cmp);
    } else {
        list_insert_key(table->table[index],
                        hash_key, key, table->cmp);
        table->used++;
    }

    if (table->used > table->size / 2)
        resize(table, table->size * 2);
}

bool contains_key(struct hash_table *table,
                  uint32_t hash_key, void *key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = hash_key & mask;
    return list_contains_key(table->table[index],
                             hash_key, key,
                             table->cmp);
}

void delete_key(struct hash_table *table,
                uint32_t hash_key, void *key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = hash_key & mask;

    if (list_contains_key(table->table[index],
                          hash_key, key, table->cmp)) {
        list_delete_key(table->table[index],
                        hash_key, key,
                        table->cmp,
                        table->destructor);
        table->used--;
    }

    if (table->used < table->size / 8)
        resize(table, table->size / 2);
}
