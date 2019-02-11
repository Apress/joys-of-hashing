
#include "open_addressing_map.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>


static uint32_t random_key()
{
    uint32_t key = (uint32_t)random();
    return key;
}

static bool compare_keys(void *ap, void *bp)
{
    uint32_t a = *(uint32_t *)ap;
    uint32_t b = *(uint32_t *)bp;
    return a == b;
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
    struct hash_table *map = empty_table(2, compare_keys, 0, 0);
    clock_t start = clock();
    for (int i = 0; i < no_elms; ++i) {
        add_map(map, keys[i], &keys[i], &keys[i]);
    }
    for (int i = 0; i < no_elms; ++i) {
        void *val = lookup_key(map, keys[i], &keys[i]);
        assert(val == &keys[i]);
    }
    uint32_t unused_key = 0;
    for (int i = 0; i < no_elms; ++i) {
        void *val = lookup_key(map, keys[i], &unused_key);
        assert(val == 0);
    }
    for (int i = 0; i < no_elms; ++i) {
        delete_key(map, keys[i], &keys[i]);
    }
    for (int i = 0; i < no_elms; ++i) {
        void *val = lookup_key(map, keys[i], &keys[i]);
        assert(val == 0);
    }
    clock_t end = clock();
    double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
    printf("%g\n", elapsed_time);
    
    free(keys);
    delete_table(map);
    
    return EXIT_SUCCESS;
}
