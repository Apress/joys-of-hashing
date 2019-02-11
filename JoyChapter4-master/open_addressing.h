
#ifndef OPEN_ADDRESSING_H
#define OPEN_ADDRESSING_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct bin {
	bool is_free : 1;
	bool is_deleted : 1;
	uint32_t key;
};

struct hash_table {
    struct bin *table;
    size_t size;
    size_t used;
    size_t active;
    double load_limit;
    // only used in primes code, but we share the header, so...
    uint32_t primes_idx;
};

struct hash_table *empty_table(size_t size, double load_limit);
void delete_table(struct hash_table *table);

void insert_key  (struct hash_table *table, uint32_t key);
bool contains_key(struct hash_table *table, uint32_t key);
void delete_key  (struct hash_table *table, uint32_t key);

#endif
