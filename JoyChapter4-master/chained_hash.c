
#include "chained_hash.h"
#include "linked_lists.h"
#include <stdlib.h>
#include <stdio.h>

#if 0
// Using insert and delete to move keys
static void resize(struct hash_table *table,
                   uint32_t new_size)
{
   // Remember these...
    uint32_t old_size = table->size;
    struct linked_list **old_bins = table->table;

    // Set up the new table
    table->table =
        (struct linked_list **)malloc(new_size * sizeof(struct linked_list *));
    for (size_t i = 0; i < new_size; ++i) {
        table->table[i] = new_linked_list();
    }
    table->size = new_size;
    table->used = 0;

    // Copy keys
    for (size_t i = 0; i < old_size; ++i) {
    struct linked_list *list = old_bins[i];
        while ( (list = list->next) ) {
            insert_key(table, list->key);
        }
    }

    // Delete old table
    for (size_t i = 0; i < old_size; ++i) {
        delete_linked_list(old_bins[i]);
    }
    free(old_bins);
}

#else

// This version copies links.
static void resize(struct hash_table *table,
                   size_t new_size)
{
    // remember these...
    uint32_t old_size = table->size;
    struct linked_list **old_bins = table->table;

    // set up the new table
    table->table =
        (struct linked_list **)malloc(new_size * sizeof(struct linked_list *));
    for (size_t i = 0; i < new_size; ++i) {
        table->table[i] = new_linked_list();
    }
    table->size = new_size;
    table->used = 0;

    // copy keys
    uint32_t mask = table->size - 1;
    for (size_t i = 0; i < old_size; ++i) {
        struct linked_list *sentinel = old_bins[i];
        struct linked_list *list = sentinel->next;
        while (list) {
            uint32_t index = list->key & mask;
            struct linked_list *next_link = list->next;
            struct linked_list *bin = table->table[index];
            list->next = bin->next;
            bin->next = list;
            table->used++;
            list = next_link;
        }
    }

    // delete old table
    for (size_t i = 0; i < old_size; ++i) {
        // Free instead of delete -- we have moved the links
        // and we only need to remove the sentinels
        free(old_bins[i]);
    }
    free(old_bins);
}
#endif

struct hash_table *empty_table(size_t size)
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
    return table;
}

void delete_table(struct hash_table *table)
{
    for (int i = 0; i < table->size; ++i) {
        delete_linked_list(table->table[i]);
    }
    free(table->table);
    free(table);
}

void insert_key(struct hash_table *table, uint32_t key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = key & mask;

    if (!contains_element(table->table[index], key)) {
        add_element(table->table[index], key);
        table->used++;
    }

    if (table->used > table->size / 2)
        resize(table, table->size * 2);
}

bool contains_key(struct hash_table *table, uint32_t key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = key & mask;
    return contains_element(table->table[index], key);
}

void delete_key(struct hash_table *table, uint32_t key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = key & mask;

    if (contains_element(table->table[index], key)) {
        delete_element(table->table[index], key);
        table->used--;
    }

    if (table->used < table->size / 8)
        resize(table, table->size / 2);
}
