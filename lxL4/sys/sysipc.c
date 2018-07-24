#include "thread.h"
#include <assert.h>
#include <likely.h>
#include <mm/vsctl.h>
#include <memlay.h>
#include <panic.h>
#include <debug.h>

void illegal_syscall(void)
{
	panic("illegal_syscall");
}

void sys_yield(void)
{
	//printstr("y");
	//printint((reg_t) current->next);
	//printstr(",");
		//printint((reg_t) (current->next->state));
	//printstr(";");
	//static int i = 0; if (!i) {
	//idle_thr.state = T_RUNNABLE; // TODO: may bug!
	// it always fuckingfully sticking to T_WAITING
	//i = 1;}
	//if (current != &idle_thr) // TODO!!!!
	assert(current->next->state == T_RUNNABLE);
	/*if (current->next->state != T_RUNNABLE) {
		printint((reg_t) current->next);
		panic("!");
	}*/
	current->rest = REST_ORIG;
	thread_switch(current->next);
	if (current->hasfault == 2) {
		ad_t pte = current->ctx.pf2_pte;
		ad_t vir = current->ctx.pf2_vir;
		assert((vir & ~PGMASK) == 0);
		v_map(vir, pte & PGMASK, pte & ~PGMASK);
		current->hasfault = 0;
		/*printstr("v_map(vir=");
		printint(vir);
		printstr(", pte=");
		printint(pte);
		printstr(")\n");
		//panic("!");*/
	}
}

static tcb_t *tcb_shift(tcb_t **phead)
{
	tcb_t *head = *phead;
	assert(head);
	*phead = head->next;
	return head;
}

static tcb_t *tcb_current_tail(void)
{
	tcb_t *tail = current;
	while (tail->next != current) {
		tail = tail->next;
		TIMES_PANIC(1024, "tcb_current_tail: too long!");
	}
	return tail;
}

void tcb_set_current_tail(void)
{
	current_tail = tcb_current_tail();
}

static void copy_data(tcb_t *to, tcb_t *from)
{
	/*memcpy(&to->ctx.unsaved_gr, &from->ctx.unsaved_gr,
			sizeof(to->ctx.unsaved_gr));*/
	memcpy(&to->ctx.gr, &from->ctx.gr, sizeof(to->ctx.gr));
}

static void copy_data_x(tcb_t *server, tcb_t *client)
{
	if (!client->hasfault) {
		copy_data(server, client);
	} else {

		assert(client->hasfault == 1);
		ad_t pf_addr = client->ctx.pf_addr & PGMASK;
		int pgrid = client->ctx.pf_addr & PGRIDMASK;
		client->ctx.pf_addr = server->ctx.sv_pf_offset = pf_addr;
		server->ctx.sv_pf_offset -= client->ps.pgrs[pgrid].beg;
		server->ctx.sv_pf_errcd = client->ctx.pf_errcd;
	}
}

static void remove_current(void)
{
	if (current == current_tail) {
		/* IDLE! */
		idle_thr.next = &idle_thr;
		current_tail = current = &idle_thr;
	} else {
		current_tail->next = current->next;
	}
}

void _sys_wait(void)
{
	assert(current->state == T_RUNNABLE);

	if (!current->pending) {
		// no pending, wait and yield
		current->state = T_WAITING;
		remove_current();
		sys_yield(); // wait for anybody

	} else {
		// has pending, run and take care of that
		tcb_t *client = current->pending;
		current->rest += client->rest;
		copy_data_x(current, client);

		pg_t shmpte = client->shmpte;
		if (current->shmmad/* && (shmpte & PG_P)*/)
			v_map(current->shmmad, shmpte & PGMASK, shmpte & ~PGMASK);
	}
}

void sys_wait(void)
{
#define HASSHMMASK 0x20000000 // TODO: move to .h?

#define S_WAIT_ENTER() \
	register reg_t ax asm ("eax"); \
	register reg_t cx asm ("ecx"); \
	int hasshm = ax & HASSHMMASK; \
	ad_t shmadr = cx & PGMASK; \
	\
	if (hasshm) { \
		if unlikely(shmadr <= KERN_END) \
			return illegal_syscall(); \
		current->shmmad = shmadr; \
	} else { \
		current->shmmad = 0; /* for sure case */ \
	}

	S_WAIT_ENTER();

	_sys_wait();

#define S_WAIT_LEAVE() \
	current->shmmad = 0;

	S_WAIT_LEAVE();
}

static void add_after_current(tcb_t *node)
{
	if (current == &idle_thr) {
		current = node;
	} else {
		node->next = current->next;
		current->next = node;
	}
}

static void copy_data_yc(tcb_t *client)
{
	if (!client->hasfault) {
		copy_data(client, current);
	} else {

		assert(client->hasfault == 1);
		ad_t buff = current->ctx.sv_buff & PGMASK;
		ad_t mask = current->ctx.sv_mask & PG_W;
		ad_t pte = v_get_mapping(buff);
		client->ctx.pf2_vir = client->ctx.pf_addr;
		client->ctx.pf2_pte = pte;
		client->hasfault = 2;
	}
}

void sys_reply(void)
{
	assert(current->state == T_RUNNABLE);

	// shift a pending, then add after current
	tcb_t *client = tcb_shift(&current->pending);
	copy_data_yc(client);
	client->state = T_RUNNABLE;
	client->rest = current->rest;
	current->rest = 0;
	add_after_current(client);
}

void sys_replywait(void)
{
	S_WAIT_ENTER();
	sys_reply();
	_sys_wait();
	S_WAIT_LEAVE();
}

static void like_current(tcb_t *node)
{
	current_tail->next = node;
	node->next = current->next;
}

static tcb_t *tcb_tail(tcb_t *head)
{
	tcb_t *tail = head;
	while (tail->next) {
		tail = tail->next;
	}
	return tail;
}

static int tcb_unshift(tcb_t **phead, tcb_t *node)
{
	if (!*phead) {
		*phead = node;
		node->next = 0;
		return 0;
	}

	node->next = *phead;
	*phead = node;

	return 1;
}

static int tcb_push(tcb_t **phead, tcb_t *node)
{
	if (!*phead) {
		*phead = node;
		node->next = 0;
		return 0;
	}

	tcb_t *tail = tcb_tail(*phead);

	node->next = 0;
	tail->next = node;

	return 1;
}


void _sys_call(tcb_t *server)
{
	assert(current->state == T_RUNNABLE);

	if (server->state == T_WAITING) {
		// server waiting! pend(*) and yield to it
		like_current(server);
		assert(!server->pending);
		tcb_unshift(&server->pending, current); // tcb_push?
		copy_data_x(server, current);
		server->state = T_RUNNABLE;
		current->state = T_BLOCKING;
		server->rest = current->rest;
		current->rest = 0;
		thread_switch(server);

	} else {
		// server not waiting :( pend and yield-away
		remove_current();
		current->state = T_CALLING;
		tcb_t *client = current;
		sys_yield();
		tcb_push(&server->pending, client);
	}
}

void sys_call(void)
{
	register reg_t ax asm ("eax");
	reg_t cx = current->ctx.cx;

	cid_t id = ax & CIDMASK;
	int hasshm = ax & HASSHMMASK;
	ad_t shmadr = cx & PGMASK;

	tcb_t *server = CAP_TCB(current, id);
	if unlikely(!server)
		return illegal_syscall();

	if (hasshm) {
		if unlikely(shmadr <= KERN_END)
			return illegal_syscall();

		pg_t shmpte = v_get_mapping(shmadr);
		if unlikely(!(shmpte & PG_P))
			return illegal_syscall();

		current->shmpte = shmpte;
	} else {
		current->shmpte = 0; /* for sure case */
	}

	if (server == &idle_thr) {
		remove_current();
		sys_yield();

	} else {
		return _sys_call(server);
	}
}

#if 0
// check for:
// https://www.ibm.com/developerworks/cn/linux/l-cn-linuxkernelint/
void _sys_hwirq(tcb_t *server){/?/}
#endif
