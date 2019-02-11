
#include "dynamic_chained_hash.h"
#include "linked_lists.h"
#include <stdlib.h>
#include <stdio.h>


static inline uint32_t
tables_idx(uint32_t x, uint32_t mask, uint32_t bits)
{ return (x & mask) >> bits; }
static inline uint32_t
sub_idx(uint32_t x, uint32_t mask)
{ return x & mask; }
static inline uint32_t
mask_bits(uint32_t no_bits)
{ return (1 << no_bits) - 1; }

static inline void
set_table_masks(struct hash_table *table)
{
    uint32_t old_bits = table->table_bits + table->k;
    uint32_t new_bits = old_bits + 1;
    table->old_tables_mask  = mask_bits(old_bits);
    table->new_tables_mask  = mask_bits(new_bits);
}
static inline uint32_t
tables_idx_from_table(struct hash_table *table, uint32_t x)
{
    uint32_t old_masked_key = x & table->old_tables_mask;
    uint32_t tmask = (table->split_count <= old_masked_key) ?
                        table->old_tables_mask :
                        table->new_tables_mask;
    return tables_idx(x, tmask, table->table_bits);
}

struct hash_table *empty_table(size_t table_bits)
{
    struct hash_table *table = malloc(sizeof(struct hash_table));
    table->table_bits = table_bits;
    table->subtable_mask = (1 << table_bits) - 1;
    table->k = 0;
    set_table_masks(table);
    table->split_count = 0;

    uint32_t size = 1 << table_bits;
    uint32_t no_tables = 1 << (table->k + 1);

    table->tables = malloc(no_tables * sizeof(subtable));
    for (uint32_t i = 0; i < no_tables; ++i) {
        table->tables[i] = malloc(size * sizeof(struct linked_list));
    }
    // initialise the first table
    for (uint32_t j = 0; j < size; ++j) {
        table->tables[0][j].next = 0;
    }
    table->allocated_tables = 2;
    table->max_bin_initialised = size;

    return table;
}

void new_delete_linked_list(struct linked_list *list)
{
    while (list) {
        struct linked_list *next = list->next;
        free(list);
        list = next;
    }
}


void delete_table(struct hash_table *table)
{
    uint32_t t_idx = 0;
    uint32_t s_idx = 0;
    uint32_t size = 1 << table->table_bits;
    for (uint32_t i = 0; i < table->max_bin_initialised; ++i) {
        subtable subtab = table->tables[t_idx];
        for (u_int32_t j = 0; j < size; ++j) {
            new_delete_linked_list(subtab[s_idx].next);
        }
        s_idx++;
        if (s_idx == size) {
            free(subtab);
            t_idx++;
            s_idx = 0;
        }
    }

    free(table->tables);
    free(table);
}

static void grow_tables(struct hash_table *table)
{
    table->split_count = 0;
    table->k++;
    set_table_masks(table);

    uint32_t old_no_tables = 1 << table->k;
    uint32_t new_no_tables = 1 << (table->k + 1);
    uint32_t size = 1 << table->table_bits;

    subtable *old_tables = table->tables;
    subtable *new_tables = malloc(new_no_tables * sizeof(subtable));
    for (uint32_t i = 0; i < old_no_tables; ++i) {
        new_tables[i] = old_tables[i];
    }
    for (uint32_t i = old_no_tables; i < new_no_tables; ++i) {
        new_tables[i] = malloc(size * sizeof(struct linked_list));
    }
    table->allocated_tables *= 2;

    table->tables = new_tables;
    free(old_tables);
}

static inline void split_bin(struct hash_table *table)
{
    uint32_t old_t_idx = tables_idx(
        table->split_count,
        table->old_tables_mask,
        table->table_bits
    );
    uint32_t new_t_idx = (1 << table->k) + old_t_idx;
    uint32_t s_idx = sub_idx(table->split_count, table->subtable_mask);

    struct linked_list *old_bin =
        &table->tables[old_t_idx][s_idx];
    struct linked_list *new_bin =
        &table->tables[new_t_idx][s_idx];
    new_bin->next = 0;
    table->max_bin_initialised++;

    uint32_t ti_mask = 1 << (table->k + table->table_bits);

    struct linked_list *list = old_bin->next; // save link to old
    old_bin->next = 0; // reset old bin

    while (list != 0) {
        struct linked_list *next = list->next;
        if (list->key & ti_mask) {
            list->next = new_bin->next;
            new_bin->next = list;
        } else {
            list->next = old_bin->next;
            old_bin->next = list;
        }
        list = next;
    }

    table->split_count++;
    // The old mask is also the maximum index into old tables
    if (table->split_count > table->old_tables_mask) {
        grow_tables(table);
    }
}

void insert_key(struct hash_table *table, uint32_t key)
{
    uint32_t t_idx = tables_idx_from_table(table, key);
    uint32_t s_idx = sub_idx(key, table->subtable_mask);

    subtable subtab = table->tables[t_idx];
    if (!contains_element(&subtab[s_idx], key)) {
        add_element(&subtab[s_idx], key);
            split_bin(table);
    }
}

bool contains_key(struct hash_table *table, uint32_t key)
{
    uint32_t t_idx = tables_idx_from_table(table, key);
    uint32_t s_idx = sub_idx(key, table->subtable_mask);
    subtable subtab = table->tables[t_idx];
    return contains_element(&subtab[s_idx], key);
}

static void shrink_tables(struct hash_table *table)
{
    uint32_t total_no_tables = 1 << (table->k + 1);
    uint32_t new_no_tables = 2 * total_no_tables;
    uint32_t size = 1 << table->table_bits;

    subtable *old_tables = table->tables;
    subtable *new_tables = malloc(new_no_tables * sizeof(subtable));
    for (uint32_t i = 0; i < new_no_tables; ++i) {
        new_tables[i] = old_tables[i];
    }

    for (uint32_t i = new_no_tables; i < 2*new_no_tables; ++i) {
        subtable subtab = table->tables[i];
        free(subtab);
    }
    free(old_tables);
    table->tables = new_tables;
    table->allocated_tables = new_no_tables;

    // When we shrink, all lists in the old tables
    // must have been initialised
    table->max_bin_initialised = size * new_no_tables;
}

static inline void merge_bin(struct hash_table *table)
{
    bool moved_table = false;
    if (table->split_count > 0) {
        table->split_count--; // FIXME: decease anyway...
    } else {
        table->k--;
        set_table_masks(table);
        table->split_count = table->old_tables_mask;
        moved_table = true;
    }

    // we use the number of tables the k indicate
    // to compare with the totally allocated tables.
    uint32_t total_no_tables = 1 << (table->k + 1);

    uint32_t old_t_idx = tables_idx(
        table->split_count,
        table->old_tables_mask,
        table->table_bits
    );

    uint32_t new_t_idx = (1 << table->k) + old_t_idx;
    uint32_t s_idx = sub_idx(table->split_count, table->subtable_mask);

    struct linked_list *old_bin =
        &table->tables[old_t_idx][s_idx];
    struct linked_list *new_bin =
        &table->tables[new_t_idx][s_idx];

    struct linked_list *list = new_bin->next;
    while (list) {
        struct linked_list *next = list->next;
        list->next = old_bin->next;
        old_bin->next = list;
        list = next;
    }
    new_bin->next = 0;

    if (total_no_tables <= 2) {
        // Do not merge below the smallest table
        return;
    }
    if (moved_table && total_no_tables <= table->allocated_tables / 4) {
        // I'm moving one index after I should, but this
        // point is slightly easier to recognize than the
        // one before.
        shrink_tables(table);
    }
}

void delete_key(struct hash_table *table, uint32_t key)
{
    uint32_t t_idx = tables_idx_from_table(table, key);
    uint32_t s_idx = sub_idx(key, table->subtable_mask);

    subtable subtab = table->tables[t_idx];
    if (contains_element(&subtab[s_idx], key)) {
        delete_element(&subtab[s_idx], key);
        merge_bin(table);
    }
}
