#include "ppm.h"
#include <likely.h>
#include <memlay.h>
#include <panic.h>

void init_ppm(void)
{
	static ad_t dma_fstk[DMA_PPM_PAGES];
	ppm_init(&ppms[PPM_DMA], dma_fstk, DMA_PPM_BEG, DMA_PPM_PAGES);
	static ad_t phys_fstk[PHYS_PPM_PAGES];
	ppm_init(&ppms[PPM_PHYS], phys_fstk, PHYS_PPM_BEG, PHYS_PPM_PAGES);
}

void ppm_init(ppm_t *ppm, ad_t *fstk,
		ad_t start, unsigned pages)
{
	ppm->free_stack = fstk;
	ppm->free_stksize = pages;
	ppm->free_stktop = -1;
	for (int i = 0; i < pages; i++) {
		ppm_free_page(ppm, start + i * PGSIZE);
	}
}

void ppm_free_page(ppm_t *ppm, ad_t page)
{
	if unlikely(ppm->free_stktop >= ppm->free_stksize)
		panic("(ppm) out of free_stack");

	ppm->free_stack[++ppm->free_stktop] = page;
}

ad_t ppm_alloc_page(ppm_t *ppm)
{
	if unlikely(ppm->free_stktop <= 0)
		panic("(ppm) out of memory");

	ad_t page = ppm->free_stack[ppm->free_stktop--];
	return page;
}
