#include <mm/vspace.h>
#include <mm/vsctl.h>
#include <umemlay.h>
#include <assert.h>
#include "thread.h"
#include <panic.h>
#include <debug.h>

/* I belive that this is policy-free */
ad_t _sys_setbrk(ad_t brk)
{
	if (!(USR_STACK_BEG <= brk && brk <= USR_STACK_END))
		return curvs->brk;
	assert((curvs->brk & ~PGMASK) == 0);
	if (curvs->brk < brk) {
		/* grow */
		ad_t pages = PGIDX(brk - curvs->brk);
		v_alloc_map_pages(curvs->brk, pages, PG_W | PG_U);
		curvs->brk = brk;
	} else if (curvs->brk > brk) {
		/* shrink */
		ad_t pages = PGIDX(curvs->brk - brk);
		v_free_unmap_pages(brk, pages);
		curvs->brk = brk;
	}
	return 0;
}

void sys_setbrk(void)
{
	register reg_t cx asm ("ecx");
	ad_t brk = cx & PGMASK;
	current->ctx.cx = _sys_setbrk(brk); // change when i chg copy_regs
}

void _sys_pagger(int pgrid, tcb_t *server, ad_t beg, ad_t end)
{
	current->ps.pgrs[pgrid].server = server;
	current->ps.pgrs[pgrid].beg = beg;
	current->ps.pgrs[pgrid].end = end;
}

void sys_pagger(void)
{
	register reg_t ax asm ("eax");
	reg_t cx = current->ctx.cx;
	reg_t dx = current->ctx.dx;
	cid_t id = ax & CIDMASK;
	int pgrid = (ax >> 16) & PGRIDMASK;
	ad_t beg = cx & PGMASK;
	ad_t end = dx;
	end = (end + PGSIZE - 1) & PGMASK;
	if (beg >= end) {
		extern void illegal_syscall(void);
		illegal_syscall();
		return;
	}
	tcb_t *server = CAP_TCB(current, id);
	_sys_pagger(pgrid, server, beg, end);
}
