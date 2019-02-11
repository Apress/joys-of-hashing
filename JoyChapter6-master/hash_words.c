
#include "hash_words.h"

uint32_t additive_hash(uint32_t state, char *input, int len)
{
    uint32_t hash = state;
    for (int i = 0; i < len; i++) {
        // combine
        hash += input[i];
    }
    return hash;
}

#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))
uint32_t rotating_hash(uint32_t state, char *input, int len)
{
    uint32_t hash = state;
    for (int i = 0; i < len; i++) {
        //      mix            combine
        hash += rot(hash, 4) ^ input[i];
    }
    return hash;
}

uint32_t one_at_a_time_hash(uint32_t state, char *input, int len)
{
    uint32_t hash = state;
    for (int i = 0; i < len; i++) {
        // combine
        hash += input[i];
        // mix
        hash += (hash << 10); hash ^= (hash >> 6);
    }

    // final mix
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

#define mix(a,b,c) \
{ \
    a -= b; a -= c; a ^= (c>>13); \
    b -= c; b -= a; b ^= (a<<8); \
    c -= a; c -= b; c ^= (b>>13); \
    a -= b; a -= c; a ^= (c>>12);  \
    b -= c; b -= a; b ^= (a<<16); \
    c -= a; c -= b; c ^= (b>>5); \
    a -= b; a -= c; a ^= (c>>3);  \
    b -= c; b -= a; b ^= (a<<10); \
    c -= a; c -= b; c ^= (b>>15); \
}
uint32_t jenkins_hash(uint32_t state, char *input, int len)
{
    uint32_t a, b; a = b = 0x9e3779b9;
    uint32_t c = state;
    int k = 0;

    //  handle most of the key
    while (len >= 12)
    {
        a += *((uint32_t*)input);
        b += *((uint32_t*)input + 4);
        c += *((uint32_t*)input + 8);
        mix(a,b,c);
        input += 12;
        len -= 12;
    }

    // handle the last 11 bytes
    c += len;
    switch(len) // all the case statements fall through
    {
        case 11: c += input[10] << 24;
        case 10: c += input[9]  << 16;
        case 9 : c += input[8]  << 8;
            // the first byte of c is reserved for the length
        case 8 : b += input[7] << 24;
        case 7 : b += input[6] << 16;
        case 6 : b += input[5] << 8;
        case 5 : b += input[4];
        case 4 : a += input[3] << 24;
        case 3 : a += input[2] << 16;
        case 2 : a += input[1] << 8;
        case 1 : a += input[0];
            // case 0: nothing left to add
    }
    mix(a,b,c);

    return c;
}

