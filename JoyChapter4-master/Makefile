
all:                            \
	array_test                  \
	dynamic_chained_hash_test   \
	chained_hash_test           \
	open_addressing_test        \
	open_addressing_prime_test

array_test: array_test.o array.o
	cc -o array_test array_test.o array.o

chained_hash_test: chained_hash_test.o chained_hash.o linked_lists.o
	cc -o chained_hash_test chained_hash_test.o chained_hash.o linked_lists.o

open_addressing_test: open_addressing_test.o open_addressing.o
	cc -o open_addressing_test open_addressing_test.o open_addressing.o

open_addressing_prime_test: open_addressing_test.o open_addressing_prime.o
	cc -o open_addressing_prime_test open_addressing_test.o open_addressing_prime.o

dynamic_chained_hash_test: dynamic_chained_hash_test.o dynamic_chained_hash.o linked_lists.o
	cc -o dynamic_chained_hash_test dynamic_chained_hash_test.o dynamic_chained_hash.o linked_lists.o
