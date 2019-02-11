
all: linked_lists_test \
	chained_hash_test \
	open_addressing_test

linked_lists_test: linked_lists_test.o linked_lists.o
	cc -o linked_lists_test linked_lists_test.o linked_lists.o

chained_hash_test: chained_hash_test.o chained_hash.o linked_lists.o
	cc -o chained_hash_test chained_hash_test.o chained_hash.o linked_lists.o

open_addressing_test: open_addressing_test.o open_addressing.o
	cc -o open_addressing_test open_addressing_test.o open_addressing.o

# DO NOT DELETE

chained_hash.o: chained_hash.h linked_lists.h
chained_hash_test.o: chained_hash.h
linked_lists.o: linked_lists.h
linked_lists_test.o: linked_lists.h
open_addressing.o: open_addressing.h
open_addressing_test.o: open_addressing.h
