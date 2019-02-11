#include "hash.h"

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

static uint32_t identity_val(uint32_t i) { return i; }
static uint32_t shift_val_2(uint32_t i) { return i << 2; }
static uint32_t shift_val_3(uint32_t i) { return i << 3; }

int main(int argc, const char *argv[])
{
    if (argc != 6) {
        printf("Usage: %s value-sampler hash-function value-space-size no-keys initial-state\n",
               argv[0]);
        return EXIT_FAILURE;
    }
    
    const char *sampler_name = argv[1];
    uint32_t (*val_sampler)(uint32_t i) = 0;
    if (strcmp(sampler_name, "identity") == 0) {
        val_sampler = identity_val;
    } else if (strcmp(sampler_name, "shift2") == 0) {
        val_sampler = shift_val_2;
    } else if (strcmp(sampler_name, "shift3") == 0) {
        val_sampler = shift_val_3;
    } else {
        printf("Unknown value sampler function.\n");
        return EXIT_FAILURE;
    }
    
    const char *hash_name = argv[2];
    uint32_t (*hash_function)(uint32_t state, uint32_t val) = 0;
    if (strcmp(hash_name, "identity") == 0) {
        hash_function = identity_hash;
    } else if (strcmp(hash_name, "additive") == 0) {
        hash_function = additive_hash;
    } else if (strcmp(hash_name, "rotating") == 0) {
        hash_function = rotating_hash;
    } else if (strcmp(hash_name, "rotating_rev") == 0) {
        hash_function = rotating_hash_rev;
    } else if (strcmp(hash_name, "one_at_a_time") == 0) {
        hash_function = one_at_a_time_hash;
    } else if (strcmp(hash_name, "one_at_a_time_rev") == 0) {
        hash_function = one_at_a_time_hash_rev;
    } else if (strcmp(hash_name, "jenkins") == 0) {
        hash_function = jenkins_hash;
    } else {
        printf("Unknown hash function.\n");
        return EXIT_FAILURE;
    }
    
    const int VALUE_SPACE_SIZE = atoi(argv[3]);
    const int NO_KEYS = atoi(argv[4]);
    const int initial_state = atoi(argv[5]);
    
    uint32_t values[VALUE_SPACE_SIZE];
    uint32_t keys_bitvector[VALUE_SPACE_SIZE];
    uint32_t keys[NO_KEYS];
    
    
    for (int i = 0; i < VALUE_SPACE_SIZE; ++i) {
        values[i] = keys_bitvector[i] = 0;
    }
    
    for (uint32_t i = 0; i < NO_KEYS; ++i) {
        uint32_t val = val_sampler(i);
        uint32_t key = hash_function(initial_state, val) & (VALUE_SPACE_SIZE-1); // mask to get into right space
        
        assert(val < VALUE_SPACE_SIZE);
        keys_bitvector[key] = values[val] = 1;
        keys[i] = key;
        
    }
    for (int i = 0; i < VALUE_SPACE_SIZE; ++i) {
        printf("values %d %d %d\n", VALUE_SPACE_SIZE, i, values[i]);
    }
    for (int i = 0; i < VALUE_SPACE_SIZE; ++i) {
        printf("hash_keys %d %d %d\n", VALUE_SPACE_SIZE, i, keys_bitvector[i]);
    }
    
    print_distribution(8, 7, keys, sizeof(keys)/sizeof(uint32_t));
    print_distribution(16, 17, keys, sizeof(keys)/sizeof(uint32_t));
    print_distribution(32, 31, keys, sizeof(keys)/sizeof(uint32_t));
    print_distribution(64, 67, keys, sizeof(keys)/sizeof(uint32_t));
    return EXIT_SUCCESS;
}
