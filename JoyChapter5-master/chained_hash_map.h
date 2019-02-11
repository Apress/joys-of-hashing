
#ifndef CHAINED_HASH_H
#define CHAINED_HASH_H

#include <stdbool.h>
#include <stdint.h>

typedef void (*destructor_func)(void *);
typedef bool (*compare_func)(void *, void *);

struct hash_table {
    struct linked_list **table;
    uint32_t size;
    uint32_t used;
    compare_func key_cmp;
    destructor_func key_destructor;
    destructor_func val_destructor;
};

struct hash_table *
empty_table(uint32_t size,
            compare_func key_cmp,
            destructor_func key_destructor,
            destructor_func val_destructor);

void delete_table(struct hash_table *table);

void add_map    (struct hash_table *table,
                 uint32_t hash_key,
                 void *key, void *value);
void delete_key (struct hash_table *table,
                 uint32_t hash_key, void *key);
void *lookup_key(struct hash_table *table,
                 uint32_t hash_key, void *key);

#endif
