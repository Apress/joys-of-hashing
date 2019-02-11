
CFLAGS=-Wall -O3

all: linked_lists_set_test linked_lists_map_test \
	chained_hash_set_test chained_hash_map_test \
	open_addressing_set_test open_addressing_map_test

linked_lists_set_test: Makefile linked_lists_set.o linked_lists_set_test.o
	cc linked_lists_set.o linked_lists_set_test.o -o linked_lists_set_test

linked_lists_map_test: Makefile linked_lists_map.o linked_lists_map_test.o
	cc linked_lists_map.o linked_lists_map_test.o -o linked_lists_map_test

chained_hash_set_test: Makefile chained_hash_set_test.o chained_hash_set.o linked_lists_set.o
	cc linked_lists_set.o chained_hash_set.o chained_hash_set_test.o -o chained_hash_set_test

chained_hash_map_test: Makefile chained_hash_map_test.o chained_hash_map.o linked_lists_map.o
	cc linked_lists_map.o chained_hash_map.o chained_hash_map_test.o -o chained_hash_map_test

open_addressing_set_test: Makefile open_addressing_set_test.o open_addressing_set.o
	cc open_addressing_set_test.o open_addressing_set.o -o open_addressing_hash_set_test

open_addressing_map_test: Makefile open_addressing_map_test.o open_addressing_map.o
	cc open_addressing_map_test.o open_addressing_map.o -o open_addressing_hash_map_test

open_addressing_set.o: open_addressing_set.h open_addressing_set.c
	cc -c $(CFLAGS) \
		open_addressing_set.c -o open_addressing_set.o

open_addressing_map.o: open_addressing_map.h open_addressing_map.c
	cc -c $(CFLAGS) \
		open_addressing_map.c -o open_addressing_map.o

linked_lists_set.o: linked_lists_set.h linked_lists_set.c
linked_lists_set_test.o: linked_lists_set.h linked_lists_set_test.c

linked_lists_map.o: linked_lists_map.h linked_lists_map.c
linked_lists_map_test.o: linked_lists_map.h linked_lists_map_test.c

chained_hash_set.o: chained_hash_set.h chained_hash_set.c linked_lists_set.h
chained_hash_set_test.o: chained_hash_set.h chained_hash_set_test.c

chained_hash_map.o: chained_hash_map.h chained_hash_map.c linked_lists_map.h
chained_hash_map_test.o: chained_hash_map.h chained_hash_map_test.c

open_addressing_set_test.o: open_addressing_set_test.c open_addressing_set.h
open_addressing_map_test.o: open_addressing_map_test.c open_addressing_map.h
