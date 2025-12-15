#include "../../include/entropy.h"

int	generate_full_int(unsigned int *seedp)
{
	uint32_t a = (uint32_t)rand_r(seedp);
	uint32_t b = (uint32_t)rand_r(seedp);
	uint32_t r = (a << 16) ^ b;
	int32_t v = (int32_t)r;

	return (int)v;
}
