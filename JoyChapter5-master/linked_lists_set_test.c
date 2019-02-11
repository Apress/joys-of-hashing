
#include "linked_lists_set.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void dummy_destructor(void *value)
{
    printf("destroying %p.\n", value);
    printf("->destroying %u.\n", *(uint32_t*)value);
}

static bool compare(void *a, void *b)
{
    return a == b;
}

int main(int argc, const char *argv[])
{
    uint32_t some_keys[] = {
        1, 2, 3, 4, 5,
    };
    size_t n = sizeof(some_keys)/sizeof(uint32_t);
    struct linked_list *list = new_linked_list();

    for (int i = 0; i < n; i++) {
        printf("inserting key %u\n", some_keys[i]);
        list_insert_key(list, some_keys[i], &some_keys[i], compare);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("is key %u in list? %d\n",
               some_keys[i],
               list_contains_key(
                   list, some_keys[i], &some_keys[i],
                   compare
               ));

        assert(list_contains_key(
            list, some_keys[i], &some_keys[i],
            compare
        ));
    }
    printf("\n");

    printf("Removing keys 3 and 4\n");
    list_delete_key(
        list,
        some_keys[2], &some_keys[2],
        compare, dummy_destructor
    );
    list_delete_key(
        list,
        some_keys[3], &some_keys[3],
        compare, dummy_destructor
    );
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("is key %u in list? %d\n",
               some_keys[i], list_contains_key(
                   list,
                   some_keys[i],
                   &some_keys[i],
                   compare
               ));
        if (some_keys[i] == 3 || some_keys[i] == 4)
            assert(!list_contains_key(
                list,
                some_keys[i],
                &some_keys[i],
                compare
            ));
        else
            assert(list_contains_key(
                list,
                some_keys[i],
                &some_keys[i],
                compare
            ));
    }
    printf("\n");

    uint32_t other_one = 11;
    printf("Contains %u %u : %d\n", some_keys[0], some_keys[0],
           list_contains_key(
               list,
               some_keys[0], &some_keys[0],
               compare
           ));
    assert(list_contains_key(
        list,
        some_keys[0], &some_keys[0],
        compare
    ));
    printf("Does not contain %u %u : %d\n", some_keys[0], other_one,
           !list_contains_key(
               list,
               some_keys[0], &other_one,
               compare
           ));
    assert(!list_contains_key(
        list,
        some_keys[0], &other_one,
        compare
    ));

    list_insert_key(list, some_keys[0], &other_one, compare);
    printf("Contains %u %u : %d\n", some_keys[0], some_keys[0],
           list_contains_key(
               list,
               some_keys[0], &some_keys[0],
               compare
           ));
    assert(list_contains_key(
        list,
        some_keys[0], &some_keys[0],
        compare
    ));
    printf("Contains %u %u : %d\n", some_keys[0], other_one,
           list_contains_key(
               list,
               some_keys[0], &other_one,
               compare
           ));
    assert(list_contains_key(
        list,
        some_keys[0], &other_one,
        compare
    ));

    list_delete_key(
        list,
        some_keys[0], &some_keys[0],
        compare, dummy_destructor
    );
    printf("Does not contain %u %u : %d\n", some_keys[0], some_keys[0],
           !list_contains_key(
               list,
               some_keys[0], &some_keys[0],
               compare
           ));
    assert(!list_contains_key(
        list,
        some_keys[0], &some_keys[0],
        compare
    ));
    printf("Contains %u %u : %d\n", some_keys[0], other_one,
           list_contains_key(
               list,
               some_keys[0], &other_one,
               compare
           ));
    assert(list_contains_key(
        list,
        some_keys[0], &other_one,
        compare
    ));

    printf("linked list: %p\n", list);
    delete_linked_list(list, dummy_destructor, true);

    return EXIT_SUCCESS;
}
