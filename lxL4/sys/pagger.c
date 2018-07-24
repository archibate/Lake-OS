#include "thread.h"
#include "pagger.h"
#include <assert.h>
#include <panic.h>
#include <debug.h>

int bigetpgr(pspace_t *ps, ad_t addr)
{
	pagger_info_t *pgrs = ps->pgrs, *pi;
	for (pi = pgrs; pi < pgrs + MAX_PAGGERS; pi++)
		if (pi->server)
			if (pi->beg <= addr && addr < pi->end)
				return pi - pgrs;

	extern void illegal_page_fault(void);
	illegal_page_fault();
}

void call_pagger(void)
{
	current->hasfault = 1;
	ad_t addr = current->ctx.pf_addr;
	int pgrid = bigetpgr(&current->ps, addr);
	current->ctx.pf_addr &= PGMASK;
	current->ctx.pf_addr |= pgrid;
	extern void _sys_call(tcb_t *server);
	_sys_call(current->ps.pgrs[pgrid].server);
}

