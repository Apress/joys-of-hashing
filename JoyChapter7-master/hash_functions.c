#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "hash_functions.h"

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
    uint8_t *T_ = (uint8_t*)T;
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[3 * no_cols + (x & mask)];

    return y;
}

uint32_t tabulation_hash_r8_q16(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 8;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 16
    uint16_t *T_ = (uint16_t*)T;
    // r == 8 -> t == 4
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[3 * no_cols + (x & mask)];

    return y;
}

uint32_t tabulation_hash_r8_q32(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 8;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 32
    uint32_t *T_ = (uint32_t*)T;
    // r == 8 -> t == 4
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[3 * no_cols + (x & mask)];

    return y;
}


uint32_t tabulation_hash_r4_q8(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 4;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 8
    uint8_t *T_ = (uint8_t*)T;
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[3 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[4 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[5 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[6 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[7 * no_cols + (x & mask)];

    return y;
}

uint32_t tabulation_hash_r4_q16(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 4;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 16
    uint16_t *T_ = (uint16_t*)T;
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[3 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[4 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[5 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[6 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[7 * no_cols + (x & mask)];

    return y;
}

uint32_t tabulation_hash_r4_q32(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 4;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 32
    uint32_t *T_ = (uint32_t*)T;
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[3 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[4 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[5 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[6 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[7 * no_cols + (x & mask)];

    return y;
}



uint32_t tabulation_hash_r2_q8(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 2;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 8
    uint8_t *T_ = (uint8_t*)T;
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 3 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 4 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 5 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 6 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 7 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 8 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 9 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[10 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[11 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[12 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[13 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[14 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[15 * no_cols + (x & mask)]; x >>= r;

    return y;
}

uint32_t tabulation_hash_r2_q16(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 2;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 16
    uint16_t *T_ = (uint16_t*)T;
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 3 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 4 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 5 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 6 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 7 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 8 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 9 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[10 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[11 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[12 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[13 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[14 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[15 * no_cols + (x & mask)]; x >>= r;

    return y;
}

uint32_t tabulation_hash_r2_q32(uint32_t x, uint8_t *T)
{
    // these are all known at compile time
    const int r = 2;
    const uint32_t no_cols = 1 << r;
    const uint32_t mask = (1 << r) - 1;

    // q == 32
    uint32_t *T_ = (uint32_t*)T;
    uint32_t y = T_[0 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 1 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 2 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 3 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 4 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 5 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 6 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 7 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 8 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[ 9 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[10 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[11 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[12 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[13 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[14 * no_cols + (x & mask)]; x >>= r;
    y ^= T_[15 * no_cols + (x & mask)]; x >>= r;

    return y;
}





uint32_t *poly_build_table(int k)
{
    return malloc(sizeof(uint32_t) * k);
}

void poly_sample(uint32_t *a, int k, uint32_t p)
{
    for (int i = 0; i < k; ++i) {
        a[i] = rand() % p;
    }
}

uint32_t poly_hash2(uint32_t x, uint32_t *a, uint32_t p)
{
    uint64_t ax1 = ((uint64_t)a[1] * (uint64_t)x) % p;
    return (uint32_t) ((a[0] + ax1) % p);
}

uint32_t poly_hash5(uint32_t x, uint32_t *a, uint32_t p)
{
    // No need for % p for the first value, it will fit.
    uint64_t x1 = (uint64_t)x;
    uint64_t x2 = (x1 * (uint64_t)x) % p;
    uint64_t x3 = (x2 * (uint64_t)x) % p;
    uint64_t x4 = (x3 * (uint64_t)x) % p;

    uint64_t a0 = (uint64_t)a[0];
    uint64_t ax1 = (uint64_t)a[1] * x1;
    uint64_t ax2 = (uint64_t)a[2] * x2;
    uint64_t ax3 = (uint64_t)a[3] * x3;
    uint64_t ax4 = (uint64_t)a[4] * x4;

    // Since all values fit in 32 bits we
    // can add them in 64 bits without overflow
    uint64_t y = a0 + ax1 + ax2 + ax3 + ax4;
    return (uint32_t) (y % p);
}

uint64_t mod_Mersenne(uint64_t x, uint8_t s)
{
    uint64_t p = (uint64_t)(1 << s) - 1; // also p
    uint64_t y = (x & p) + (x >> s);
    return (y > p) ? y - p : y;
}

uint32_t poly_hash2_Mersenne(uint32_t x, uint32_t *a, uint8_t s)
{
    uint64_t ax1 = mod_Mersenne((uint64_t)a[1] * (uint64_t)x, s);
    uint32_t y = (uint32_t) mod_Mersenne(a[0] + ax1, s);
    return y;
}

uint32_t poly_hash5_Mersenne(uint32_t x, uint32_t *a, uint8_t s)
{
    // No need for % p for the first value, it will fit.
    uint64_t x1 = (uint64_t)x;
    uint64_t x2 = mod_Mersenne(x1 * (uint64_t)x, s);
    uint64_t x3 = mod_Mersenne(x2 * (uint64_t)x, s);
    uint64_t x4 = mod_Mersenne(x3 * (uint64_t)x, s);

    uint64_t a0 = (uint64_t)a[0];
    uint64_t ax1 = (uint64_t)a[1] * x1;
    uint64_t ax2 = (uint64_t)a[2] * x2;
    uint64_t ax3 = (uint64_t)a[3] * x3;
    uint64_t ax4 = (uint64_t)a[4] * x4;

    // Since all values fit in 32 bits we
    // can add them in 64 bits without overflow
    uint64_t y = a0 + ax1 + ax2 + ax3 + ax4;
    return (uint32_t) mod_Mersenne(y, s);
}
