
#include "hash.h"

uint32_t identity_hash(uint32_t state, uint32_t input)
{
    return input;
}

uint32_t additive_hash(uint32_t state, uint32_t input)
{
    uint32_t hash = state;
    uint8_t *p = (uint8_t*)&input;
    
    // combine
    hash += *(p++);
    hash += *(p++);
    hash += *(p++);
    hash += *p;
    
    return hash;
}

#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))
uint32_t rotating_hash(uint32_t state, uint32_t input)
{
    uint32_t hash = state;
    uint8_t *p = (uint8_t*)&input;
    
    //      mix          ; combine
    hash ^=                *(p++);
    hash += rot(hash, 4) ^ *(p++);
    hash += rot(hash, 4) ^ *(p++);
    hash += rot(hash, 4) ^ *p;

    return hash;
}

uint32_t rotating_hash_rev(uint32_t state, uint32_t input)
{
    uint32_t hash = state;
    uint8_t *p = ((uint8_t*)&input) + 3;
    
    //      mix          ; combine
    hash ^=                *(p--);
    hash += rot(hash, 4) ^ *(p--);
    hash += rot(hash, 4) ^ *(p--);
    hash += rot(hash, 4) ^ *p;
    
    return hash;
}

uint32_t one_at_a_time_hash(uint32_t state, uint32_t input)
{
    uint32_t hash = state;
    uint8_t *p = (uint8_t*)&input;
    
    // combine    ; mix
    hash += *(p++); hash += (hash << 10); hash ^= (hash >> 6);
    hash += *(p++); hash += (hash << 10); hash ^= (hash >> 6);
    hash += *(p++); hash += (hash << 10); hash ^= (hash >> 6);
    hash += *p;     hash += (hash << 10); hash ^= (hash >> 6);
    
    // final mix
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash;
}

uint32_t one_at_a_time_hash_rev(uint32_t state, uint32_t input)
{
    uint32_t hash = state;
    uint8_t *p = ((uint8_t*)&input) + 3;
    
    // combine    ; mix
    hash += *(p--); hash += (hash << 10); hash ^= (hash >> 6);
    hash += *(p--); hash += (hash << 10); hash ^= (hash >> 6);
    hash += *(p--); hash += (hash << 10); hash ^= (hash >> 6);
    hash += *p;     hash += (hash << 10); hash ^= (hash >> 6);
    
    // final mix
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash;
}

uint32_t jenkins_hash(uint32_t state, uint32_t input)
{
    uint32_t a, b; a = b = 0x9e3779b9;
    uint32_t c = state;
    
    // combine
    a += input;
    
    // mix
    a -= b; a -= c; a ^= (c>>13);
    b -= c; b -= a; b ^= (a<<8);
    c -= a; c -= b; c ^= (b>>13);
    a -= b; a -= c; a ^= (c>>12);
    b -= c; b -= a; b ^= (a<<16);
    c -= a; c -= b; c ^= (b>>5);
    a -= b; a -= c; a ^= (c>>3);
    b -= c; b -= a; b ^= (a<<10);
    c -= a; c -= b; c ^= (b>>15);

    return c;
}

