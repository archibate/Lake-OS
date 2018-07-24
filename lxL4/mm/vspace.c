#include "vspace.h"
#include "vsvpt.h"
#include <umemlay.h>
#include <string.h>
#include <mm/ppm.h>
#include <mm/mmu.h>
#include <dma.h>

/* vspace setup */

static void pgd_setup_selfmap(pgp_t pgd)
{
	// self-mapping is cool!
	// see https://blog.csdn.net/shybrian/article/details/6730814
	// for more details!
	pgd[SELFMAP_IDX] = (ad_t) pgd | PG_P | PG_W;
}

static void pgd_copy_dma_pdes(pgp_t pgd)
{
	// temperary, we don't wanna enable PGE at all (todo)
	// also, NOTE that kernel-area mappings are never changed.
	// since it's a microkernel, only DMA is used in kernel-area
	memcpy(pgd, _pgd, DMA_PGTS * sizeof(pg_t));
}

void vspace_init(vspace_t *vs)
{
	vs->pgd = (pgp_t) alloc_page(PPM_DMA);
	/* can also be PPM_PHYS, but need a temp map to setup it */
	vs->brk = USR_STACK_BEG;

	pgd_copy_dma_pdes(vs->pgd);
	pgd_setup_selfmap(vs->pgd);
}

vspace_t *curvs;

void vspace_switch(vspace_t *vs)
{
	if (vs == curvs)
		return;
	curvs = vs;
	if (curvs->pgd)
		mmu_set_pgd(curvs->pgd);
}
