#pragma once

#include <sizet.h>

#if 0
void show_heap_info(void);
#endif
void *malloc(size_t size);
void *calloc(size_t nitems, size_t size);
void *realloc(void *old_p, size_t new_size);
void free(void *p);
