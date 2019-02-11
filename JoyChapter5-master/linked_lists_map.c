
#include "linked_lists_map.h"
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
    sentinel->value = 0;
    sentinel->next = 0;
    return sentinel;
}

void delete_linked_list(struct linked_list *list,
                        destructor_func key_destructor,
                        destructor_func val_destructor,
                        bool free_resources)
{
    while (list != 0) {
        struct linked_list *next = list->next;
        if (free_resources && key_destructor && list->key)
            key_destructor(list->key);
        if (free_resources && val_destructor && list->value)
            val_destructor(list->value);
        free(list);
        list = next;
    }
}

void list_add_map(struct linked_list *list,
                  uint32_t hash_key,
                  void *key, void *value)
{
    struct linked_list *link =
        (struct linked_list*)malloc(
            sizeof(struct linked_list)
        );
    link->hash_key = hash_key;
    link->key = key;
    link->value = value;
    link->next = list->next;
    list->next = link;
}

static struct linked_list *
get_previous_link(struct linked_list *list,
                  uint32_t hash_key, void *key,
                  compare_func key_cmp)
{
    while (list->next) {
        if (list->next->hash_key == hash_key &&
            key_cmp(list->next->key, key))
            return list;
        list = list->next;
    }
    return 0;
}

bool list_delete_key(struct linked_list *list,
                     uint32_t hash_key, void *key,
                     compare_func key_cmp,
                     destructor_func key_destructor,
                     destructor_func val_destructor)
{
    struct linked_list *link =
        get_previous_link(list, hash_key, key, key_cmp);
    if (!link) return false;

    // we need to get rid of link->next
    struct linked_list *to_delete = link->next;
    link->next = to_delete->next;
    if (key_destructor) key_destructor(to_delete->key);
    if (val_destructor) val_destructor(to_delete->value);
    free(to_delete);
    return true;
}

struct linked_list *
list_lookup_key(struct linked_list *list,
                uint32_t hash_key, void *key,
                compare_func key_cmp)
{
    struct linked_list *link =
        get_previous_link(list, hash_key, key, key_cmp);
    return link ? link->next : 0;
}
