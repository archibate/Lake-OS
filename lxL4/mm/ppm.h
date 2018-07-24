#pragma once

#include <page.h>

typedef struct ppm {
	ad_t *free_stack;
	int free_stktop, free_stksize;
} ppm_t;

typedef enum ppm_type {
	PPM_DMA = 0,
	PPM_PHYS,
	MAX_PPMS,
} ppm_type_t;
ppm_t ppms[MAX_PPMS];

void ppm_init(ppm_t *ppm, ad_t *fstk,
		ad_t start, unsigned pages);
ad_t ppm_alloc_page(ppm_t *ppm);
void ppm_free_page(ppm_t *ppm, ad_t page);

#define alloc_page(type) ppm_alloc_page(&ppms[type])
#define free_page(type, page) ppm_free_page(&ppms[type], page)
