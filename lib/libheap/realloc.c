#include "malloc.h"
#include <string.h>
#include "heap.h"

void *realloc(void *old_p, size_t new_size)
{
	if (!old_p)
		return malloc(new_size);
	struct heap_hdr *hdr = (struct heap_hdr *) old_p;
	hdr--;
	size_t old_size = hdr->len;
	void *new_p = malloc(new_size);
	size_t copy_size = old_size > new_size ? old_size : new_size;
	memcpy(new_p, old_p, copy_size);
	return new_p;
}
