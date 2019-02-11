
#ifndef CHAINED_HASH_H
#define CHAINED_HASH_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

struct hash_table {
    struct linked_list **table;
    size_t size;
    size_t used;
};

struct hash_table *empty_table(size_t size);
void delete_table(struct hash_table *table);
void insert_key  (struct hash_table *table, uint32_t key);
bool contains_key(struct hash_table *table, uint32_t key);
void delete_key  (struct hash_table *table, uint32_t key);

#endif
