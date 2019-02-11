
#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <stdlib.h>
#include <stdbool.h>

struct linked_list {
    uint32_t hash_key;
    void *key;
    void *value;
    struct linked_list *next;
};

typedef void (*destructor_func)(void *);
typedef bool (*compare_func)(void *, void *);

struct linked_list *new_linked_list();

void delete_linked_list(struct linked_list *list,
                        destructor_func key_destructor,
                        destructor_func val_destructor,
                        bool free_resouces);

void list_add_map   (struct linked_list *list,
                     uint32_t hash_key,
                     void *key, void *value);
bool list_delete_key(struct linked_list *list,
                     uint32_t hash_key, void *key,
                     compare_func key_cmp,
                     destructor_func key_destructor,
                     destructor_func value_destructor);
struct linked_list *
list_lookup_key     (struct linked_list *list,
                     uint32_t hash_key, void *key,
                     compare_func key_cmp);

#endif
