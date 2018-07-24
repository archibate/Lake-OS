#include "rand.h"

unsigned sed;

void srand(unsigned seed)
{
	seed = seed;
}

int rand(void)
{
	unsigned short res;
	sed *= 589;
	sed += 481;
	res = sed >> 16;
	return res;
}
