
#include "open_addressing_set.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

static uint32_t random_key()
{
    uint32_t key = (uint32_t)random();
    return key;
}

static bool compare_values(void *a, void *b)
{
    return a == b; // pointer comparison. Works for this test.
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s no_elements\n", argv[0]);
        return EXIT_FAILURE;
    }

    int no_elms = atoi(argv[1]);
    uint32_t *keys = (uint32_t *)malloc(no_elms * sizeof(uint32_t));
    for (int i = 0; i < no_elms; ++i) {
        keys[i] = random_key();
    }
    struct hash_table *table = empty_table(2, compare_values, 0);
    clock_t start = clock();
    for (int i = 0; i < no_elms; ++i) {
        insert_key(table, keys[i], &keys[i]);
    }
    for (int i = 0; i < no_elms; ++i) {
        assert(contains_key(table, keys[i], &keys[i]));
    }
    for (int i = 0; i < no_elms; ++i) {
        assert(!contains_key(table, random_key(), 0));
    }
    for (int i = 0; i < no_elms; ++i) {
        delete_key(table, keys[i], &keys[i]);
    }
    for (int i = 0; i < no_elms; ++i) {
        assert(!contains_key(table, keys[i], &keys[i]));
    }
    clock_t end = clock();
    double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    printf("%g\n", elapsed_time);

    free(keys);
    delete_table(table);

    return EXIT_SUCCESS;
}
