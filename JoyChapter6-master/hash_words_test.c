#include "hash_words.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void print_distribution(int mask_size, int prime_size,
                        uint32_t keys[], uint32_t no_keys)
{
    int mask_table[mask_size];
    for (int i = 0; i < mask_size; ++i) {
        mask_table[i] = 0;
    }
    
    int prime_table[prime_size];
    for (int i = 0; i < prime_size; ++i) {
        prime_table[i] = 0;
    }
    
    int bitmask = mask_size - 1;
    for (int i = 0; i < no_keys; ++i) {
        mask_table[keys[i] & bitmask]++;
        prime_table[keys[i] % prime_size]++;
    }
    
    for (int i = 0; i < mask_size; ++i) {
        printf("mask %d %d %d\n", mask_size, i, mask_table[i]);
    }
    for (int i = 0; i < prime_size; ++i) {
        printf("prime %d %d %d\n", prime_size, i, prime_table[i]);
    }
}

void read_words (FILE *f, char **words, int no_words)
{
    /* assumes no word exceeds length of 1023 */
    char x[1024];
    for (int i = 0; i < no_words; ++i) {
        int res = fscanf(f, " %1023s", x);
        assert(res == 1);
        words[i] = strdup(x);
    }
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s hash-function\n",
               argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *hash_name = argv[1];
    uint32_t (*hash_function)(uint32_t state, char *val, int len) = 0;
    if (strcmp(hash_name, "additive") == 0) {
        hash_function = additive_hash;
    } else if (strcmp(hash_name, "rotating") == 0) {
        hash_function = rotating_hash;
    } else if (strcmp(hash_name, "one_at_a_time") == 0) {
        hash_function = one_at_a_time_hash;
    } else if (strcmp(hash_name, "jenkins") == 0) {
        hash_function = jenkins_hash;
    } else {
        printf("Unknown hash function.\n");
        return EXIT_FAILURE;
    }
    
    int no_keys = 627;
    char **keys = malloc(no_keys * sizeof(char*));
    FILE *input_file = fopen("walrus.txt", "r");
    read_words(input_file, keys, no_keys);
    fclose(input_file);
    
    uint32_t hash_keys[no_keys];
    for (uint32_t i = 0; i < no_keys; ++i) {
        uint32_t key = hash_function(0, keys[i], strlen(keys[i]));
        hash_keys[i] = key;
    }
    
    print_distribution(8, 7, hash_keys, sizeof(hash_keys)/sizeof(uint32_t));
    print_distribution(16, 17, hash_keys, sizeof(hash_keys)/sizeof(uint32_t));
    print_distribution(32, 31, hash_keys, sizeof(hash_keys)/sizeof(uint32_t));
    print_distribution(64, 67, hash_keys, sizeof(hash_keys)/sizeof(uint32_t));
    
    free(keys);
    
    return EXIT_SUCCESS;
}
