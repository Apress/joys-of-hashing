
#ifndef OPEN_ADDRESSING_H
#define OPEN_ADDRESSING_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct bin {
	int is_free : 1;
	int is_deleted : 1;
	uint32_t key;
};

struct hash_table {
	struct bin *table;
    size_t size;
};

struct hash_table *empty_table(size_t size);
void delete_table(struct hash_table *table);

void insert_key   (struct hash_table *table, uint32_t key);
bool contains_key (struct hash_table *table, uint32_t key);
void delete_key   (struct hash_table *table, uint32_t key);


#endif
