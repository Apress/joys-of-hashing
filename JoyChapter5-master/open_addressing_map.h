
#ifndef OPEN_ADDRESSING_H
#define OPEN_ADDRESSING_H

#include <stdbool.h>
#include <stdint.h>

typedef void (*destructor_func)(void *);
typedef bool (*compare_func)(void *, void *);

struct bin {
    bool is_free : 1;
    bool is_deleted : 1;
    uint32_t hash_key;
    void *key;
    void *value;
};

struct hash_table {
    struct bin *table;
    uint32_t size;
    uint32_t used;
    uint32_t active;
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

void add_map       (struct hash_table *table,
                    uint32_t hash_key,
                    void *key, void *value);
void delete_key    (struct hash_table *table,
                    uint32_t hash_key, void *key);
void *lookup_key   (struct hash_table *table,
                    uint32_t hash_key, void *key);

#endif
