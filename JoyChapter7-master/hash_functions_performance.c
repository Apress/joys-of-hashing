#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "hash_functions.h"

int
main(int argc, char **argv)
{
	clock_t tick, tack;
	int	no_samples = 10;
	int	loop = 100000;	//for comparison with heuristic functions

	char *operation = "init";
	if (argc > 1)
		operation = argv[1];

    uint32_t x = rand();

	uint32_t p = 32;
	uint32_t r, q, t, m;
	uint32_t no_cols, bytes;
	uint8_t  *T8;
	uint16_t *T16;
	uint32_t *T32, *T32_end;

    uint32_t k;
    uint32_t *a;

	//set random number generator seed.
	srand(1234);

	if (strcmp(operation, "init") == 0) {


        p = (uint32_t)(1 << 31) - 1; // Prime for poly
		k = 2;
		a = poly_build_table(k);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    poly_sample(a, k, p);
            }
			tack = clock();
			printf("Polynomial_%d %zu\n", k, tack - tick);
		}
		free(a);

		k = 5;
		a = poly_build_table(k);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
			for (int j = 0; j < loop; ++j) {
                poly_sample(a, k, p);
            }
			tack = clock();
			printf("Polynomial_%d %zu\n", k, tack - tick);
		}
		free(a);

		p = 32; // word size for tabulation
	    r = 2 ; q = 8;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 2 ; q = 16;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 2 ; q = 32;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 4 ; q = 8;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 4 ; q = 16;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 4 ; q = 32;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 8 ; q = 8;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 8 ; q = 16;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 8 ; q = 32;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		T32 = (uint32_t*)T8;
		T32_end = (uint32_t*)(T8 + bytes);
    	for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_sample(T32, T32_end);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);



	} else { // init

	    r = 8 ; q = 8;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r8_q8(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 8 ; q = 16;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r8_q16(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 8 ; q = 32;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r8_q32(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 4 ; q = 8;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r4_q8(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 4 ; q = 16;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r4_q16(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 4 ; q = 32;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r4_q32(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);


	    r = 2 ; q = 8;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r2_q8(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 2 ; q = 16;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r2_q16(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);

	    r = 2 ; q = 32;
	    no_cols = (1 << r);
    	t = p / r;
    	no_cols = (1 << r);
    	bytes = t * no_cols * q / 8;
    	T8 = malloc(bytes);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
            for (int j = 0; j < loop; ++j) {
			    tabulation_hash_r2_q32(x, T8);
            }
			tack = clock();
			printf("Tabulation_%d_%d %zu\n", r, q, tack - tick);
		}
		free(T8);






        p = (uint32_t)(1 << 31) - 1; // reusing as prime
        k = 2;
		a = poly_build_table(k);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
			for (int j = 0; j < loop; ++j) {
                poly_hash2(x, a, p);
            }
			tack = clock();
			printf("Polynomial_2 %zu\n", tack - tick);
		}
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
			for (int j = 0; j < loop; ++j) {
                poly_hash2_Mersenne(x, a, 31);
            }
			tack = clock();
			printf("PolynomialMer_2 %zu\n", tack - tick);
		}
		free(a);

        k = 5;
		a = poly_build_table(k);
		for (int i = 0; i < no_samples; ++i) {
			tick = clock();
			for (int j = 0; j < loop; ++j) {
                poly_hash5(x, a, p);
            }
			tack = clock();
			printf("Polynomial_5 %zu\n", tack - tick);
		}
        for (int i = 0; i < no_samples; ++i) {
			tick = clock();
			for (int j = 0; j < loop; ++j) {
                poly_hash5_Mersenne(x, a, p);
            }
			tack = clock();
			printf("PolynomialMer_5 %zu\n", tack - tick);
		}
		free(a);
    }

	return EXIT_SUCCESS;
}
