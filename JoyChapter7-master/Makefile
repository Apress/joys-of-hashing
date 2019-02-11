
CFLAGS=-O3

all: performance rehash_test rehash_performance

performance: hash_functions.o hash_functions_performance.o
	cc -O3 -o performance hash_functions.o hash_functions_performance.o

rehash_test: rehash_test.o open_addressing.o
	cc -O3 -o rehash_test rehash_test.o open_addressing.o

rehash_performance: rehash_performance.o open_addressing.o
	cc -O3 -o rehash_performance rehash_performance.o open_addressing.o

hash_functions.o: hash_functions.h
open_addressing.o: open_addressing.h
