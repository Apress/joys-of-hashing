
#include "chained_hash.h"
#include "linked_lists.h"
#include <stdlib.h>

struct hash_table *empty_table(size_t size)
{
    struct hash_table *table =
      (struct hash_table*)malloc(sizeof(struct hash_table));
    table->table =
      (struct linked_list **)malloc(size * sizeof(struct linked_list *));
    for (size_t i = 0; i < size; ++i) {
        table->table[i] = new_linked_list();
    }
    table->size = size;
    return table;
}

void delete_table(struct hash_table *table)
{
    for (size_t i = 0; i < table->size; ++i) {
        delete_linked_list(table->table[i]);
    }
    free(table->table);
    free(table);
}

void insert_key(struct hash_table *table, uint32_t key)
{
    uint32_t mask = table->size - 1;
    uint32_t index = key & mask;
    if (!contains_element(table->table[index], key))
        add_element(table->table[index], key);
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
    delete_element(table->table[index], key);
}
