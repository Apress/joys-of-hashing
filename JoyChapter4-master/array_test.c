
#include "array.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, const char *argv[])
{
    struct array *array = new_array(1);
    
    for (int i = 0; i < 10; ++i) {
        append(array, i);
    }
    for (int j = 0; j < 10; ++j) {
        int i = get(array, j);
        assert(i == j);
        printf("Expected %d and got %d.\n", j, i);
    }
    for (int j = 0; j < 10; ++j) {
        set(array, j, 10*j);
        int i = get(array, j);
        assert(i == 10*j);
        printf("Expected %d and got %d.\n", 10*j, i);
    }
    
    free(array);
    
    return EXIT_SUCCESS;
}

