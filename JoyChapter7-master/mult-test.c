#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void check16()
{
    uint16_t x = 1 << 15, y = (1 << 15) - 1;
    uint16_t z1 = x * y; // overflow
    uint32_t z2 = x * y; // OK, the mult is actually in 32
    uint32_t z3 = (uint32_t)x * (uint32_t)y; // ditto
    printf("%u %u %u\n", z1, z2, z3);

}

void check32()
{
    uint32_t x = 1 << 31, y = (uint32_t)(1 << 31) - 1;
    uint32_t z1 = x * y; // overflow (32-bit mult)
    uint64_t z2 = x * y; // same overflow
    uint64_t z3 = (uint64_t)x * (uint64_t)y; // ok
    printf("%u %llu %llu\n", z1, z2, z3);

}

uint64_t mod_Mersenne(uint64_t x, uint8_t s)
{
    uint64_t p = (uint64_t)(1 << s) - 1; // also p
    uint64_t y = (x & p) + (x >> s);
    return (y > p) ? y - p : y;
}

void tabulation_sample(uint32_t *start, uint32_t *end)
{
    while (start != end)
        *(start++) = rand();
}

uint32_t tabulation_hash_r8_q8(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 8;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 8
    uint8_t *_T = (uint8_t*)T;
    uint32_t y;
    y ^= T_[3 * no_cols + (x & mask)]; x >> r;
    y ^= T_[2 * no_cols + (x & mask)]; x >> r;
    y ^= T_[1 * no_cols + (x & mask)]; x >> r;
    y ^= T_[0 * no_cols + (x & mask)];

    return y;
}

uint32_t tabulation_hash_r8_q8(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 8;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 8
    uint8_t *_T = (uint8_t*)T;
    uint32_t y;
    y ^= T_[3 * no_cols + (x & mask)]; x >> r;
    y ^= T_[2 * no_cols + (x & mask)]; x >> r;
    y ^= T_[1 * no_cols + (x & mask)]; x >> r;
    y ^= T_[0 * no_cols + (x & mask)];

    return y;
}

int main(int argc, const char **argv)
{
#if 0
    check16();
    check32();

    printf("%u\n", 2 & 7);
    printf("%u %u\n", 2 >> 7, (uint32_t)2 >> 3);
    printf("%u\n", (2 % 7) + (2 >> 3));
    uint64_t p = (uint64_t)(1 << 3) - 1;
    printf("p == %llu\n", p);
    uint64_t y = (2 & p) + (2 >> 3);
    printf("y == %llu (%d %llu)\n", y,  y > p, (y > p) ? y - p : y);
    printf("%u %llu\n", 2 % 7, mod_Mersenne(2, 3));
#endif

    int p = 32;
    int r = 8;
    int no_cols = (1 << r);
    int q = 8;
    int t = p / r;
    int bytes = t * no_cols * q / 8;

    printf("t x no_cols = %u x %u\n", t, no_cols);
    uint8_t *T8 = malloc(bytes);
    tabulation_sample((uint32_t*)T8, (uint32_t*)(T8 + bytes));

    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < no_cols; ++j) {
            printf("%d ", T8[i * no_cols + j]);
        }
        printf("\n");
    }
    free(T8);
    printf("\n");

    r = 8 ; q = 16;
    no_cols = (1 << r);
    t = p / r;
    no_cols = (1 << r);
    bytes = t * no_cols * q / 8;
    T8 = malloc(bytes);
    tabulation_sample((uint32_t*)T8, (uint32_t*)(T8 + bytes));

    printf("t x no_cols = %u x %u\n", t, no_cols);
    no_cols = (1 << r);
    t = 32 / r;
    uint16_t *T16 = (uint16_t*)T8;
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < no_cols; ++j) {
            printf("%d ", T16[i * no_cols + j]);
        }
        printf("\n");
    }
    free(T8);

    r = 8 ; q = 32;
    no_cols = (1 << r);
    t = p / r;
    no_cols = (1 << r);
    bytes = t * no_cols * q / 8;
    T8 = malloc(bytes);
    tabulation_sample((uint32_t*)T8, (uint32_t*)(T8 + bytes));

    printf("t x no_cols = %u x %u\n", t, no_cols);
    uint32_t *T32 = (uint16_t*)T8;
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < no_cols; ++j) {
            printf("%d ", T32[i * no_cols + j]);
        }
        printf("\n");
    }
    free(T8);

    return EXIT_SUCCESS;
}
