
#include "array.h"
#include <stdlib.h>
#include <assert.h>


struct array *new_array(int initial_size)
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    array->array = (int *)malloc(initial_size * sizeof(int));
    array->used = 0;
    array->size = initial_size;
    return array;
}

void delete_array(struct array *array)
{
    free(array->array);
    free(array);
}

static void resize(struct array *array, unsigned int new_size)
{
    assert(new_size >= array->used);
    array->array = (int *)realloc(array->array, new_size * sizeof(int));
}

void append(struct array *array, int value)
{
    if (array->used == array->size)
        resize(array, 2 * array->size);
    array->array[array->used++] = value;
}

int get(struct array *array, int index)
{
    assert(array->used > index);
    return array->array[index];
}

void set(struct array *array, int index, int value)
{
    assert(array->used > index);
    array->array[index] = value;
}

int pop(struct array *array)
{
    assert(array->used > 0);
    int top = array->array[--(array->used)];
    if (array->used < array->size / 4)
        resize(array, array->size / 2);
    return top;
}


