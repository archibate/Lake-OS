#pragma once

typedef enum thread_state {
	T_INACTIVE = 0,
	T_RUNNABLE,
	T_WAITING,
	T_CALLING,
	T_BLOCKING,
} thread_state_t;
#define REST_ORIG 10

#include "cspace.h"
#include <mm/vspace.h>
#include "pspace.h"

typedef struct tcb {
	ctx_t ctx; // lxL4:tss-direct-iframe (TDI)
	struct tcb *next; // tickyield
	struct tcb *pending; // call/reply
	unsigned char state; // L4:threadstate
	unsigned char hasfault; // pagger (sigma0)
	short rest; // L4:donation
	cspace_t cs; // seL4:cap
	vspace_t vs; // seL4:vspace
	pspace_t ps; // pagger (sigma0)
	union {
		pg_t shmpte;
		pg_t shmmad;
	}; // lxL4:shmipc
} tcb_t;

#define CAP_TCB(thr, id) ((thr)->cs.caps[(id)].tcb)
//#define CAP_TCB(thr, id) (CS_GET_CAP(&((thr)->cs), id)->tcb)
