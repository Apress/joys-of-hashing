
#ifndef OPEN_ADDRESSING_H
#define OPEN_ADDRESSING_H

#include <stdbool.h>
#include <stdint.h>

struct bin {
    bool is_free : 1;
    bool is_deleted : 1;
    unsigned int key;
};

struct hash_table {
    struct bin *table;
    unsigned int size;
    unsigned int used;
    unsigned int active;

    // For tabulation hashing.
    uint8_t *T, *T_end;

    float rehash_factor;
    unsigned int probe_limit;
    unsigned int operations_since_rehash;
};

struct hash_table *empty_table(uint32_t size,
                               float rehash_factor);
void   delete_table(struct hash_table *table);
void   insert_key  (struct hash_table *table, uint32_t key);
bool   contains_key(struct hash_table *table, uint32_t key);
void   delete_key  (struct hash_table *table, uint32_t key);

#endif
