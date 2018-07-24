#include "thread.h"
#include <string.h>

tcb_t idle_thr;
ctx_t idle_stack;
extern void __attribute__((noreturn)) cpu_idle(void);

void init_idle(void)
{
	memset(&idle_thr, 0, sizeof(idle_thr));
	current = &idle_thr;
	kernel_context_init(&current->ctx, (reg_t) &cpu_idle,
			(reg_t) (&idle_stack + 1), 0x202);
	current->next = current;
	current->state = T_RUNNABLE;
}
