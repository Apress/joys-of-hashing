
#include "chained_hash_map.h"
#include "linked_lists_map.h"
#include <stdlib.h>

struct hash_table *empty_table(uint32_t size,
                               compare_func key_cmp,
                               destructor_func key_destructor,
                               destructor_func val_destructor)
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
    table->key_cmp = key_cmp;
    table->key_destructor = key_destructor;
    table->val_destructor = val_destructor;
    return table;
}

void delete_table(struct hash_table *table)
{
    for (int i = 0; i < table->size; ++i) {
        delete_linked_list(table->table[i],
                           table->key_destructor,
                           table->val_destructor,
                           true);
    }
    free(table->table);
    free(table);
}

static void resize(struct hash_table *table, uint32_t new_size)
{
    // Remember these...
    uint32_t old_size = table->size;
    struct linked_list **old_bins = table->table;

    // Set up the new table
    table->table =
        (struct linked_list **)malloc(
               new_size * sizeof(struct linked_list *)
        );
    for (int i = 0; i < new_size; ++i) {
        table->table[i] = new_linked_list();
    }
    table->size = new_size;
    table->used = 0;

    // Copy maps
    for (int i = 0; i < old_size; ++i) {
        struct linked_list *list = old_bins[i];
        while ( (list = list->next) ) {
            add_map(table, list->hash_key,
                    list->key, list->value);
        }
    }

    // Delete old table
    for (int i = 0; i < old_size; ++i) {
        delete_linked_list(old_bins[i],
                           table->key_destructor,
                           table->val_destructor,
                           false);
    }
    free(old_bins);
}


void add_map(struct hash_table *table,
             uint32_t hash_key,
             void *key, void *value)
{
    uint32_t mask = table->size - 1;
    uint32_t index = hash_key & mask;
    struct linked_list *list = table->table[index];

    struct linked_list *link =
        list_lookup_key(list, hash_key, key, table->key_cmp);

    if (link != 0) {
        // the key exists in the table, replace the value.
        if (table->key_destructor)
            table->key_destructor(link->key);
        if (table->val_destructor)
            table->val_destructor(link->value);
        link->key = key;
        link->value = value;
    } else {
        // the key is new, so insert it and the value
        list_add_map(list, hash_key, key, value);

        table->used++;
    }

    if (table->used > table->size / 2)
        resize(table, table->size * 2);
}


void delete_key(struct hash_table *table,
                uint32_t hash_key, void *key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = hash_key & mask;
    struct linked_list *list = table->table[index];
    bool deleted = list_delete_key(
        list, hash_key, key, table->key_cmp,
        table->key_destructor, table->val_destructor
    );

    if (deleted) table->used--;

    if (table->used < table->size / 8)
        resize(table, table->size / 2);
}

void *lookup_key(struct hash_table *table,
                 uint32_t hash_key, void *key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = hash_key & mask;
    struct linked_list *list = table->table[index];
    struct linked_list *link =
        list_lookup_key(list, hash_key, key, table->key_cmp);
    return link ? link->value : 0;
}
