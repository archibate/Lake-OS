#include <sys/context.h>
#include <mm/vspace.h>
#include <sys/thread.h>
#include <debug.h>
#include <panic.h>
#include <asm.h>

#if 0
void int_hand_0e(ctx_t *ctx)
{
	reg_t cr2 = io_get_cr2();
	dump_context(ctx);
	printstr("cr2=");
	printint(cr2);
	panic("int_hand_0d #PF!");
}
#else
#define get_pf_addr io_get_cr2
void int_hand_0e(ctx_t *ctx)
{
	ad_t vir = get_pf_addr();
	if (!(ctx->errcd & PG_U)) {
		dump_context(ctx);
		printstr("cr2=");
		printint(vir);
		panic("#PF in kernel");
	}
	assert(ctx == &current->ctx);

	reg_t errcd = current->ctx.errcd;
	assert(errcd);
	current->ctx.pf_addr = vir;
	current->ctx.pf_errcd = errcd;
	extern void call_pagger(void);
	call_pagger();
}
#endif

void illegal_page_fault(void)
{
	dump_context(&current->ctx);
	printstr("cr2=");
	printint(io_get_cr2());
	panic("page fault in non-paged area");
}
