
#ifndef HASH_H
#define HASH_H

#include <stdint.h>


uint32_t additive_hash(uint32_t state, char *input, int len);
uint32_t rotating_hash(uint32_t state, char *input, int len);
uint32_t one_at_a_time_hash(uint32_t state, char *input, int len);
uint32_t jenkins_hash(uint32_t state, char *input, int len);

#endif
