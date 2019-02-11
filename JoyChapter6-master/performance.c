#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"

int main(int argc, char **argv)
{
    clock_t tick, tack;   
    int no_rep = 10;
    int loop = 100000;

    for (int j = 0; j < no_rep; ++j) {
        tick = clock();
        for (int i = 0; i < loop; ++i) {
            identity_hash(i, i);
        }
        tack = clock();
        printf("identity %zu\n", tack - tick);
    }

    for (int j = 0; j < no_rep; ++j) {
        tick = clock();
        for (int i = 0; i < loop; ++i) {
            additive_hash(i, i);
        }
        tack = clock();
        printf("additive %zu\n", tack - tick);
    }
    
    for (int j = 0; j < no_rep; ++j) {
        tick = clock();
        for (int i = 0; i < loop; ++i) {
            rotating_hash(i, i);
        }
        tack = clock();
        printf("rotating %zu\n", tack - tick);
    }

    for (int j = 0; j < no_rep; ++j) {
        tick = clock();
        for (int i = 0; i < loop; ++i) {
            one_at_a_time_hash(i, i);
        }
        tack = clock();
        printf("one_at_a_time %zu\n", tack - tick);
    }

    for (int j = 0; j < no_rep; ++j) {
        tick = clock();
        for (int i = 0; i < loop; ++i) {
            jenkins_hash(i, i);
        }
        tack = clock();
        printf("Jenkins %zu\n", tack - tick);
    }

    return EXIT_SUCCESS;
}