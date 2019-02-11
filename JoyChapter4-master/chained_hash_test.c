
#include "chained_hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

static unsigned int random_key()
{
    unsigned int key = (unsigned int)random();
    return key;
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s no_elements\n", argv[0]);
        return EXIT_FAILURE;
    }

    int no_elms = atoi(argv[1]);
    unsigned int *keys = (unsigned int *)malloc(no_elms * sizeof(unsigned int));
    for (int i = 0; i < no_elms; ++i) {
        keys[i] = random_key();
    }
    struct hash_table *table = empty_table(2);
    clock_t start = clock();
    for (int i = 0; i < no_elms; ++i) {
        insert_key(table, keys[i]);
    }
    for (int i = 0; i < no_elms; ++i) {
        assert(contains_key(table, keys[i]));
    }
    for (int i = 0; i < no_elms; ++i) {
        (void)contains_key(table, random_key());
    }
    for (int i = 0; i < no_elms; ++i) {
        delete_key(table, keys[i]);
    }
    for (int i = 0; i < no_elms; ++i) {
        assert(!contains_key(table, keys[i]));
    }
    clock_t end = clock();
    double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    printf("%g\n", elapsed_time);

    free(keys);
    delete_table(table);

    return EXIT_SUCCESS;
}
