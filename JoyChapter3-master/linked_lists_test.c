
#include "linked_lists.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, const char *argv[])
{
    size_t some_keys[] = {
        1, 2, 3, 4, 5,
    };
    size_t n = sizeof(some_keys)/sizeof(size_t);
    struct linked_list *list = new_linked_list();
    
    for (int i = 0; i < n; i++) {
        printf("inserting key %lu\n", some_keys[i]);
        add_element(list, some_keys[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("is key %lu in list? %d\n",
               some_keys[i], contains_element(list, some_keys[i]));
        
        assert(contains_element(list, some_keys[i]));
    }
    printf("\n");
    
    printf("Removing keys 3 and 4\n");
    delete_element(list, 3);
    delete_element(list, 4);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("is key %lu in list? %d\n",
               some_keys[i], contains_element(list, some_keys[i]));
        if (some_keys[i] == 3 || some_keys[i] == 4)
            assert(!contains_element(list, some_keys[i]));
        else
            assert(contains_element(list, some_keys[i]));
    }
    printf("\n");

    delete_linked_list(list);
    
    return EXIT_SUCCESS;
}
