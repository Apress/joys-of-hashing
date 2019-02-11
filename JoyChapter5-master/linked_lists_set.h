
#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <stdlib.h>
#include <stdbool.h>

struct linked_list {
    uint32_t hash_key;
    void *key;
    struct linked_list *next;
};

typedef void (*destructor_func)(void *);
typedef bool (*compare_func)(void *, void *);

struct linked_list *new_linked_list();

void delete_linked_list(struct linked_list *list,
                        destructor_func destructor,
                        bool free_keys);

void list_insert_key     (struct linked_list *list,
                          uint32_t hash_key, void *key,
                          compare_func cmp);
bool list_contains_key   (struct linked_list *list,
                          uint32_t hash_key, void *key,
                          compare_func cmp);
void list_delete_key     (struct linked_list *list,
                          uint32_t hash_key, void *key,
                          compare_func cmp,
                          destructor_func destructor);

#endif
