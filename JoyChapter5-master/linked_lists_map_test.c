
#include "linked_lists_map.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void dummy_destructor(void *value)
{
    printf("destroying %p.\n", value);
    printf("\tdestroying %u.\n", *(uint32_t*)value);
}
static bool key_compare(void *a, void *b)
{
    return a == b;
}

int main(int argc, const char *argv[])
{
    uint32_t some_keys[] = {
        1, 2, 3, 4, 5,
    };
    uint32_t some_values[] = {
        11, 12, 13, 14, 15,
    };
    size_t n = sizeof(some_keys)/sizeof(uint32_t);
    struct linked_list *list = new_linked_list();

    for (int i = 0; i < n; i++) {
        printf("inserting key %u\n", some_keys[i]);
        list_add_map(list, some_keys[i],
                &some_keys[i],
                &some_values[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        struct linked_list *link = list_lookup_key(
            list, some_keys[i], &some_keys[i], key_compare
        );
        assert(link != 0);
        uint32_t key = *((uint32_t *)link->key);
        uint32_t value = *((uint32_t *)link->value);
        printf("is key %u in list? %u -> %u\n",
               some_keys[i], key, value);

        
    }
    printf("\n");

    printf("Removing keys 3 and 4\n");
    list_delete_key(list,
                    some_keys[2], &some_keys[2],
                    key_compare,
                    dummy_destructor,
                    dummy_destructor
                   );
    list_delete_key(list,
                    some_keys[3], &some_keys[3],
                    key_compare,
                    dummy_destructor,
                    dummy_destructor
                   );
    printf("\n");
    for (int i = 0; i < n; i++) {
        struct linked_list *link =
            list_lookup_key(
                list, some_keys[i], &some_keys[i], key_compare
            );
        if (link) {
            uint32_t key = *((uint32_t *)link->key);
            uint32_t value = *((uint32_t *)link->value);
            printf("is key %u in list? %u -> %u\n",
                   some_keys[i], key, value);
        } else {
            printf("is key %u in list? NO!\n", some_keys[i]);
        }
        
        
        
    }
    printf("\n");
    
    delete_linked_list(list,
                       dummy_destructor,
                       dummy_destructor, true);

    return EXIT_SUCCESS;
}
