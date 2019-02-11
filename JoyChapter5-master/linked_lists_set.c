
#include "linked_lists_set.h"
#include <assert.h>

/* We represent linked lists using a sentinel link at the beginning of the list.
   This makes it easier to insert and remove elements without having to return
   updated lists.
 */

struct linked_list *new_linked_list()
{
    struct linked_list *sentinel =
        (struct linked_list*)malloc(sizeof(struct linked_list));
    sentinel->hash_key = 0;
    sentinel->key = 0;
    sentinel->next = 0;
    return sentinel;
}

void delete_linked_list(struct linked_list *list,
                        destructor_func destructor,
                        bool free_keys)
{
    while (list) {
        struct linked_list *next = list->next;
        if (free_keys && destructor && list->key)
            destructor(list->key);
        free(list);
        list = next;
    }
}

static struct linked_list *
get_previous_link(struct linked_list *list,
                  uint32_t hash_key, void *key,
                  compare_func cmp)
{
    while (list->next) {
        if (list->next->hash_key == hash_key &&
                cmp(list->next->key, key))
            return list;
        list = list->next;
    }
    return 0;
}

void list_insert_key(struct linked_list *list,
                     uint32_t hash_key,
                     void *key,
                     compare_func cmp)
{
    // build link and put it at the front of the list.
    // the hash table checks for duplicates if we want to avoid those
    struct linked_list *new_link =
        (struct linked_list*)malloc(sizeof(struct linked_list));
    new_link->hash_key = hash_key;
    new_link->key = key;
    new_link->next = list->next;
    list->next = new_link;
}

void list_delete_key(struct linked_list *list,
                     uint32_t hash_key,
                     void *key,
                     compare_func cmp,
                     destructor_func destructor)
{
    struct linked_list *link =
        get_previous_link(list, hash_key, key, cmp);
    if (!link) return;

    struct linked_list *to_delete = link->next;
    link->next = to_delete->next;
    if (destructor) destructor(to_delete->key);
    free(to_delete);
}

bool list_contains_key(struct linked_list *list,
                       uint32_t hash_key,
                       void *key,
                       compare_func cmp)
{
    return get_previous_link(list, hash_key, key, cmp) != 0;
}
