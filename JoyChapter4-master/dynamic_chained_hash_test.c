
#include "dynamic_chained_hash.h"
#include "linked_lists.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

void print_table(struct hash_table *table) 
{
    printf("table->table_bits: %u\n", table->table_bits);
    printf("table->split_count: %u\n", table->split_count);
    printf("table->subtable_mask: %u\n", table->subtable_mask);
    printf("table->old_tables_mask: %u\n", table->old_tables_mask);
    printf("table->new_tables_mask: %u\n", table->new_tables_mask);

    uint32_t no_complete_tables = 1 << table->k;
    uint32_t total_no_tables = 1 << (table->k + 1);
    uint32_t initialised = table->max_bin_initialised;


    uint32_t size = 1 << table->table_bits;
    printf("\n");
    for (uint32_t i = 0; i < no_complete_tables; ++i) {
        printf("-------\n");
        printf("TABLE %u\n", i);
        printf("-------\n");
        subtable subtab = table->tables[i];
        for (u_int32_t j = 0; j < size; ++j) {
            printf("bin[%.2u] => ", j);
            struct linked_list *list = &subtab[j];
            for (list = list->next; list != 0; list = list->next) {
                printf("%u(%u) ", list->key, list->key & table->subtable_mask);
            }
            printf("\n");
        }
        printf("-------\n\n");
    }
    uint32_t break_count = table->split_count;
    for (uint32_t i = no_complete_tables; i < total_no_tables; ++i) {
        printf("-------\n");
        printf("TABLE %u\n", i);
        printf("-------\n");
        subtable subtab = table->tables[i];
        for (u_int32_t j = 0; j < size; ++j) {
            if (break_count-- == 0) goto done;
            printf("bin[%.2u] => ", j);
            struct linked_list *list = &subtab[j];
            for (list = list->next; list != 0; list = list->next) {
                printf("%u(%u) ", list->key, list->key & table->subtable_mask);
            }
            printf("\n");
        }
    }
done:
        printf("competed %u, max %u\n", no_complete_tables, initialised);
        printf("-------\n\n");
    printf("\n");
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s no_elements\n", argv[0]);
        return EXIT_FAILURE;
    }

    int no_elms = atoi(argv[1]);

    srand(time(0));
    unsigned int *keys = (unsigned int *)malloc(no_elms * sizeof(unsigned int));
    for (int i = 0; i < no_elms; ++i) {
        keys[i] = rand();
    }

    struct hash_table *table = empty_table(2);
    print_table(table);

    insert_key(table, 1);
    insert_key(table, 2);
    print_table(table);
    delete_key(table, 2);
    print_table(table);

    printf("Inserting keys\n");
    printf("-------------------------------\n");
    for (int i = 0; i < no_elms; ++i) {
        //insert_key(table, (1 << 2) | i);
        insert_key(table,  i);
        insert_key(table, keys[i]);
        print_table(table);
    }
    print_table(table);

    // just checking that we do not add existing keys
    printf("----duplications---\n");
    for (int i = 0; i < no_elms; ++i) {
        assert(contains_key(table, i));
        //insert_key(table, (1 << 2) | i);
        insert_key(table,  i);
        insert_key(table, keys[i]);
        assert(contains_key(table, keys[i]));
    }
    print_table(table);

    printf("----deleting---\n");
    for (int i = 0; i < no_elms; ++i) {
        assert(contains_key(table, keys[i]));
        delete_key(table, keys[i]);
        assert(!contains_key(table, keys[i]));
    }
    print_table(table);
    for (int i = 0; i < no_elms; ++i) {
        printf("deleting %u\n", i);
        assert(contains_key(table, i));
        delete_key(table, i);
        assert(!contains_key(table, i));
        print_table(table);
    }

    delete_table(table);

    return EXIT_SUCCESS;
}
