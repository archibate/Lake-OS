#include <lxL4/page.h>
#include "pgalloc.h"
#include "malloc.h"

struct pgalc_hdr {
	void *beg_p;
};

void *pgalloc(void)
{
	// TODO: very bad!
	void *p = malloc(2 * PGSIZE + sizeof(struct pgalc_hdr));
	ad_t ad = (ad_t) p;
	ad += PGSIZE;
	ad &= PGMASK;
	struct pgalc_hdr *pghdr = (struct pgalc_hdr *) ad;
	pghdr--;
	pghdr->beg_p = p;
	return (void *) ad;
}

void pgfree(void *p)
{
	struct pgalc_hdr *pghdr = (struct pgalc_hdr *) p;
	pghdr--;
	free(pghdr->beg_p);
}
