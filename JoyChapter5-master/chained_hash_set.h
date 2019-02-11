
#ifndef CHAINED_HASH_H
#define CHAINED_HASH_H

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t (*hash_func)(void *);
typedef void (*destructor_func)(void *);
typedef bool (*compare_func)(void *, void *);

struct hash_table {
    struct linked_list **table;
    uint32_t size;
    uint32_t used;
    compare_func cmp;
    destructor_func destructor;
};

struct hash_table *
empty_table        (uint32_t size,
                    compare_func cmp,
                    destructor_func destructor);
void delete_table  (struct hash_table *table);

void insert_key  (struct hash_table *table,
                  uint32_t hash_key, void *key);
bool contains_key(struct hash_table *table,
                  uint32_t hash_key, void *key);
void delete_key  (struct hash_table *table,
                  uint32_t hash_key, void *key);

#endif
