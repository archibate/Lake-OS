#pragma once

#include "context.h"
#include <assert.h>
#include <x86/tss.h>
#include "tcb.h"

extern tcb_t *current, *current_tail;
extern tcb_t idle_thr;

#define thread_inactive(thr) ((thr)->state == T_INACTIVE)
#define thread_runnable(thr) ((thr)->state == T_RUNNABLE)
#define thread_send_blocked(thr) ((thr)->state == T_SEND_BLOCKED)
#define thread_recv_blocked(thr) ((thr)->state == T_RECV_BLOCKED)
#define thread_deactive(thr) ((thr)->state = T_INACTIVE)
#define thread_active(thr) ((thr)->state = T_RUNNABLE)
#define thread_block_on_send(thr) ((thr)->state = T_SEND_BLOCKED)
#define thread_block_on_recv(thr) ((thr)->state = T_RECV_BLOCKED)
void __attribute__((fastcall)) _thread_switch(tcb_t *thr);
void thread_schedule(void);
static void thread_switch(tcb_t *thr)
{
	_thread_switch(thr);
	extern void tcb_set_current_tail(void);
	tcb_set_current_tail();
}
