#pragma once

#include <ad_t.h>

void *pgalloc(void);
void pgfree(void *p);

static inline ad_t alloc_page(void)
{
	return (ad_t) pgalloc();
}

static inline void free_page(ad_t addr)
{
	pgfree((void *) addr);
}
