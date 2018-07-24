#include "thread.h"
#include <assert.h>

tcb_t *current, *current_tail;

void __attribute__((fastcall)) _thread_switch(tcb_t *thr)
{
	if (thr == current)
		return;
	current_tail = current;
	current = thr;
	reg_t esp0 = (reg_t) (&current->ctx + 1);
	set_tss0_esp0(esp0);
	vspace_switch(&current->vs);
}
