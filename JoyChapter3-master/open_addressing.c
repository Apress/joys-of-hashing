
#include "open_addressing.h"
#include <stdlib.h>
#include <string.h>

// Pick probing strategy
#define LINEAR_PROBING


#ifdef LINEAR_PROBING
static uint32_t
p(uint32_t k, uint32_t i, uint32_t m)
{
    return (k + i) & (m - 1);
}
#else
// DOUBLE HASHING
static uint32_t
p(uint32_t k, uint32_t i, uint32_t m)
{
    uint32_t h1 = k;
    uint32_t h2 = (k << 1) | 1;
    return (h1 + i*h2) & (m - 1);
}
#endif

struct hash_table *empty_table(size_t size)
{
    struct hash_table *table =
        (struct hash_table*)malloc(sizeof(struct hash_table));
    table->table = (struct bin *)malloc(size * sizeof(struct bin));
    for (size_t i = 0; i < size; ++i) {
        struct bin *bin = & table->table[i];
        bin->is_free = true;
        bin->is_deleted = false;
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
    uint32_t index;
    struct bin *bin;
    for (size_t i = 0; i < table->size; ++i) {
        index = p(key, i, table->size);
        bin = & table->table[index];
        if (bin->is_free || bin->is_deleted || bin->key == key)
            break;
    }
    bin->is_free = bin->is_deleted = false;
    bin->key = key;
}

bool contains_key(struct hash_table *table, uint32_t key)
{
    for (size_t i = 0; i < table->size; ++i) {
        uint32_t index = p(key, i, table->size);
        struct bin *bin = & table->table[index];
        if (bin->is_free)
            return false;
        if (!bin->is_deleted && bin->key == key)
            return true;
    }
    return false;
}

void delete_key(struct hash_table *table, uint32_t key)
{
    for (size_t i = 0; i < table->size; ++i) {
        uint32_t index = p(key, i, table->size);
        struct bin *bin = & table->table[index];
        if (bin->is_free) return;
        if (bin->key == key) {
            bin->is_deleted = true;
            return;
        }
    }
}

