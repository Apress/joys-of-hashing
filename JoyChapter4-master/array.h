
#ifndef ARRAY_H
#define ARRAY_H

struct array {
    int *array;
    unsigned int size;
    unsigned int used;
};

struct array *new_array(int initial_size);
void delete_array(struct array *array);

void append (struct array *array, int value);
int  get    (struct array *array, int index);
void set    (struct array *array, int index, int value);
int  pop    (struct array *array);

#endif
