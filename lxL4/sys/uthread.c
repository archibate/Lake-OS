#include "cthread.h"
#include "uthread.h"
#include <mm/vspace.h>
#include <mm/vsctl.h>
#include <string.h>
#include <umemlay.h>
#include <mm/ppm.h>
#include <debug.h>
#include <panic.h>

static void vo_alloc_stack(vspace_t *vs)
{
	const int init_stkpgs = 1;
	v_alloc_map_pages(USR_STACK_END - init_stkpgs * PGSIZE,
			init_stkpgs, PG_W | PG_U);
}

static void vo_setup_code(const ucode_t *code)
{
#define MAXPAGES(size) (((size) - 1) / PGSIZE + 1)
	v_alloc_map_pages(USR_CODE_BEG, MAXPAGES(code->size), PG_W | PG_U);
	memcpy((void *) USR_CODE_BEG, code->data, code->size);
}

void uthread_run(tcb_t *thr, const ucode_t *code)
{
	thread_setup(thr, USR_CODE_BEG, USR_STACK_END);

	vspace_init(&thr->vs);
	vspace_switch(&thr->vs);
	vo_alloc_stack(&thr->vs);
	vo_setup_code(code);

#if 0
	printstr("thr->ctx.ip=");
	printint(thr->ctx.ip);
	printstr("\n");
	printstr("code->data=");
	printint((reg_t) code->data);
	printstr("\n");
	printstr("code->size=");
	printint(code->size);
	printstr("\n");
#endif
}
