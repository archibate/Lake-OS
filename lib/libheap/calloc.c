#include "malloc.h"
#include <string.h>
#include "heap.h"

void *calloc(size_t nitems, size_t size)
{
	size *= nitems;
	void *p = malloc(size);
	memset(p, 0, size);
}

