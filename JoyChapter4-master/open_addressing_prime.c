
#include "open_addressing.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

// Primes for 1.66 growth
int primes[] = { 2, 5, 11, 19, 37, 67, 113, 191, 331, 557, 929, 1543, 2579, 4283, 7121, 11821, 19661, 32647, 54217, 90001, 149411, 248033, 411737, 683489, 1134607, 1883459, 3126547, 5190071, 8615527, 14301779 };

static size_t no_primes = sizeof(primes)/sizeof(int);

static unsigned int
p(unsigned int k, unsigned int i, unsigned int m)
{
    return (k + i) % m;
}

static void resize(struct hash_table *table, unsigned int new_size)
{
    // remember the old bins until we have moved them.
    struct bin *old_bins = table->table;
    unsigned int old_size = table->size;

    // Update table so it now contains the new bins (that are empty)
    table->table = (struct bin *)malloc(new_size * sizeof(struct bin));
    struct bin *end = table->table + new_size;
    for (struct bin *bin = table->table; bin != end; ++bin) {
        bin->is_free = true;
        bin->is_deleted = false;
    }
    table->size = new_size;
    table->active = table->used = 0;

    // the move the values from the old bins to the new, using the table's
    // insertion function
    end = old_bins + old_size;
    for (struct bin *bin = old_bins; bin != end; ++bin) {
        if (bin->is_free || bin->is_deleted) continue;
        insert_key(table, bin->key);
    }

    // finally, free memory for old bins
    free(old_bins);
}


struct hash_table *empty_table(size_t size, double load_limit)
{
    size = primes[0];
    struct hash_table *table =
        (struct hash_table*)malloc(sizeof(struct hash_table));
    table->table = (struct bin *)malloc(size * sizeof(struct bin));
    struct bin *end = table->table + size;
    for (struct bin *bin = table->table; bin != end; ++bin) {
        bin->is_free = true;
        bin->is_deleted = false;
    }
    table->size = size;
    table->active = table->used = 0;
    table->load_limit = load_limit;
    table->primes_idx = 0;
    return table;
}

void delete_table(struct hash_table *table)
{
    free(table->table);
    free(table);
}


void insert_key(struct hash_table *table, unsigned int key)
{
    unsigned int index;
    for (unsigned int i = 0; i < table->size; ++i) {
        index = p(key, i, table->size);
        struct bin *bin = & table->table[index];

        if (bin->is_free) {
            bin->key = key;
            bin->is_free = bin->is_deleted = false;

            // we have one more active element
            // and one more unused cell changes character
            table->active++; table->used++;
            break;
        }

        if (bin->is_deleted) {
            bin->key = key;
            bin->is_free = bin->is_deleted = false;

            // we have one more active element
            // but we do not use more cells since the
            // deleted cell was already used.
            table->active++;
            break;
        }
    }

    if (table->used > table->load_limit * table->size) {
        assert(table->primes_idx + 1 < no_primes);
        resize(table, primes[++(table->primes_idx)]);
    }
}

bool contains_key(struct hash_table *table, unsigned int key)
{
    for (unsigned int i = 0; i < table->size; ++i) {
        unsigned int index = p(key, i, table->size);
        struct bin *bin = & table->table[index];
        if (bin->is_free)
            return false;
        if (!bin->is_deleted && bin->key == key)
            return true;
    }
    return false;
}

void delete_key(struct hash_table *table, unsigned int key)
{
    for (unsigned int i = 0; i < table->size; ++i) {
        unsigned int index = p(key, i, table->size);
        struct bin * bin = & table->table[index];
        if (bin->is_free)
            return;
        if (!bin->is_deleted && bin->key == key) {
            bin->is_deleted = true;
            table->active--;
            break;
        }
    }

    if (table->active < table->load_limit / 4 * table->size &&
        table->primes_idx > 0) {
        resize(table, primes[--(table->primes_idx)]);
    }
}

