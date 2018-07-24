#include "cthread.h"
#include <string.h>
#include <assert.h>

void thread_setup(tcb_t *thr, reg_t ip, reg_t sp)
{
	memset(thr, 0, sizeof(tcb_t));
	context_init(&thr->ctx, ip, sp, 0x3202);
	thr->next = thr;
	thr->rest = REST_ORIG;
	thr->state = T_RUNNABLE;
}
