
#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <stdlib.h>
#include <stdbool.h>

struct linked_list {
    uint32_t key;
    struct linked_list *next;
};

struct linked_list *new_linked_list();
void delete_linked_list(struct linked_list *list);

void add_element(struct linked_list *list, uint32_t key);
void delete_element(struct linked_list *list, uint32_t key);
bool contains_element(struct linked_list *list, uint32_t key);

#endif
