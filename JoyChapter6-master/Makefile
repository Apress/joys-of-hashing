
all: hash_test hash_map hash_words_test performance

hash_test: hash_test.o hash.o
	cc -o hash_test hash_test.o hash.o

hash_map: hash_map.o hash.o
	cc -o hash_map hash_map.o hash.o

hash_words_test: hash_words_test.o hash_words.o
	cc -o hash_words_test hash_words_test.o hash_words.o

performance: performance.o hash.o
	cc -O3 -o performance performance.o hash.o

hash.o: hash.h
hash_test.o: hash.h
hash_map.o: hash.h
hash_words.o: hash_words.h
hash_words_test.o: hash_words.h
