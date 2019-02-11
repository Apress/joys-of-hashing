
#include "open_addressing.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

static unsigned int random_key()
{
    unsigned int key = (unsigned int)random();
    return key;
}

void print_table(struct hash_table *table)
{
    struct bin *b = table->table;
    struct bin *table_end = table->table + table->size;
    for (; b != table_end; b++) {
        if (!b->is_free || b->is_deleted) {
            printf("key %u in table\n", b->key);
        }
    }
}

bool power_of_two(uint32_t x)
{
    return (x != 0) && ((x & (x - 1)) == 0);
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s size no_elements\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint32_t size = atoi(argv[1]);
    uint32_t no_elms = atoi(argv[2]);

    if (!power_of_two(size)) {
        printf("the size must be a power of two.\n");
        return EXIT_FAILURE;
    }
    
    // for random states, use: srand((unsigned) time(&t));
    srand(0); // fix the seed for experiments
    
    unsigned int *keys = 
        (unsigned int *)malloc(no_elms * sizeof(unsigned int));
    for (int i = 0; i < no_elms; ++i) {
        keys[i] = random_key();
    }

    struct hash_table *table = empty_table(size, 1);
    for (int i = 0; i < no_elms; ++i) {
        insert_key(table, keys[i]);
        assert(contains_key(table, keys[i]));
    }
    for (int i = 0; i < no_elms; ++i) {
        assert(contains_key(table, keys[i]));
    }
    for (int i = 0; i < no_elms; ++i) {
        (void)contains_key(table, random_key());
    }
    for (int i = 0; i < no_elms; ++i) {
        delete_key(table, keys[i]);
        assert(!contains_key(table, keys[i]));
    }
    for (int i = 0; i < no_elms; ++i) {
        assert(!contains_key(table, keys[i]));
    }
    free(keys);
    delete_table(table);

    printf("DONE\n");

    return EXIT_SUCCESS;
}
