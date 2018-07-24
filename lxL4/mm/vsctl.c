#include "vsctl.h"
#include "vsvpt.h"
#include "ppm.h"
#include "mmu.h"
#include <likely.h>
#include <assert.h>

/* mapping rules */

#define MAPPING_IDXS(vir) \
	assert(!(vir & ~PGMASK)); \
	unsigned ptes_idx = PGIDX(vir); \
	unsigned pgt_idx = PGT_IDX(ptes_idx); \
	unsigned pgd_idx = PGD_IDX(ptes_idx);

#define v_invalidate(vir) mmu_invalidate((ad_t) (vir))
#define pg_present(pge) ((pge) & PG_P)

void v_map(ad_t vir, ad_t phy, unsigned attr)
{
	MAPPING_IDXS(vir);

	attr |= PG_P;
	pg_t pte = phy | attr;

	if (!pg_present(VPD[pgd_idx])) {
		unsigned pde_attr = PG_P | PG_W | PG_U;
		// let the pdes to have the 'best' attr
		// the attr of pte will limits it
		ad_t pgt = alloc_page(PPM_PHYS);
		VPD[pgd_idx] = pgt | pde_attr;
		v_invalidate(VPT + ptes_idx);
	}

	VPT[ptes_idx] = pte;
	v_invalidate(vir);
}

int v_unmap(ad_t vir)
{
	MAPPING_IDXS(vir);

	if unlikely(!pg_present(VPD[pgd_idx]))
		return 0;

	VPT[ptes_idx] = 0;
	v_invalidate(vir);
	return 1;
}

pg_t v_unmap_s(ad_t vir)
{
	MAPPING_IDXS(vir);

	if unlikely(!pg_present(VPD[pgd_idx]))
		return 0;

	pg_t old_pte = VPT[ptes_idx];
	VPT[ptes_idx] = 0;
	v_invalidate(vir);
	return old_pte;
}

int v_has_vpde(ad_t vir)
{
	MAPPING_IDXS(vir);

	return pg_present(VPD[pgd_idx]);
}

pg_t v_get_mapping(ad_t vir)
{
	MAPPING_IDXS(vir);

	// NOTE that we don't except any #PF in vpt
	if (!v_has_vpde(vir))
		return 0;

	return VPT[ptes_idx];
}

#if 0
void v_free_vpd(void)
{
	for (int idx = DMA_PGTS; idx < 0x3ff; idx++) {
		ad_t pt_addr = VPD[idx]; // including this pd!
		free_page(idx == SELFMAP_IDX ? PPM_DMA : PPM_PHYS, pt_addr);
	}
	// dangerous! please switch to another vspace as soon as possible
}
#endif

void v_alloc_map_pages(ad_t pos, int count, unsigned attr)
{
	while (count-- >= 0) {
		ad_t page = alloc_page(PPM_PHYS);
		v_map(pos, page, attr);
		pos += PGSIZE;
	}
}

void v_free_unmap_pages(ad_t pos, int count)
{
	while (count-- >= 0) {
		pg_t pte = v_unmap_s(pos);
		assert(pg_present(pte));
		ad_t page = pte & PGMASK;
		free_page(PPM_PHYS, page);
		pos += PGSIZE;
	}
}
