#ifndef HASH_FUNCTIONS
#define HASH_FUNCTIONS

#include <stdint.h>

void tabulation_sample(uint32_t *start, uint32_t *end);

uint32_t tabulation_hash_r4_q8 (uint32_t x, uint8_t *T);
uint32_t tabulation_hash_r4_q16(uint32_t x, uint8_t *T);
uint32_t tabulation_hash_r4_q32(uint32_t x, uint8_t *T);

uint32_t tabulation_hash_r8_q8 (uint32_t x, uint8_t *T);
uint32_t tabulation_hash_r8_q16(uint32_t x, uint8_t *T);
uint32_t tabulation_hash_r8_q32(uint32_t x, uint8_t *T);

uint32_t tabulation_hash_r2_q8 (uint32_t x, uint8_t *T);
uint32_t tabulation_hash_r2_q16(uint32_t x, uint8_t *T);
uint32_t tabulation_hash_r2_q32(uint32_t x, uint8_t *T);

uint32_t *poly_build_table(int k);
void      poly_sample(uint32_t *a, int k, uint32_t p);
uint32_t poly_hash2(uint32_t x, uint32_t *a, uint32_t p);
uint32_t poly_hash5(uint32_t x, uint32_t *a, uint32_t p);
uint32_t poly_hash2_Mersenne(uint32_t x, uint32_t *a, uint8_t s);
uint32_t poly_hash5_Mersenne(uint32_t x, uint32_t *a, uint8_t s);

#endif