
#include "open_addressing.h"
#include <stdlib.h>
#include <stdio.h>

static unsigned int random_key()
{
    unsigned int key = (unsigned int)random();
    if (key == 0 || key == 1) return 2;
    return key;
}


int main(int argc, const char *argv[])
{
    int n = 10;
    size_t keys[n];
    for (int i = 0; i < n; ++i) {
        keys[i] = random_key();
    }
    
    struct hash_table *table = empty_table(32);
    for (int i = 0; i < n; ++i) {
        printf("inserting key %lu\n", keys[i]);
        insert_key(table, keys[i]);
    }
    printf("\n");
    
    for (int i = 0; i < n; ++i) {
        printf("is key %lu in table? %d\n", keys[i],
               contains_key(table, keys[i]));
    }
    printf("\n");
    
    printf("Removing keys 3 and 4 (%lu and %lu)\n", keys[3], keys[4]);
    delete_key(table, keys[3]);
    delete_key(table, keys[4]);
    printf("\n");
    
    for (int i = 0; i < n; ++i) {
        printf("is key %lu in table? %d\n", keys[i],
               contains_key(table, keys[i]));
    }
    printf("\n");
    
    delete_table(table);
    
    return EXIT_SUCCESS;
}

