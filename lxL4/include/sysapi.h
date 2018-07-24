#pragma once

#include <reg_t.h>
#include "cid.h"

#define mk_syscall_s(ax, ...) asm volatile (__VA_ARGS__ "a" (ax));

#define SYSCALL_INT_NR 0x67
#define __sysc_int_0_i(i) "int $" #i ";"
#define sysc_int_0_i(i) __sysc_int_0_i(i)
#define sysc_int_0 sysc_int_0_i(SYSCALL_INT_NR)
#define sysc_int_0br "mov %11, %%ebp;" sysc_int_0 "mov %%ebp, %5;"
#define sysc_int_1br "push %%ebp;" sysc_int_0br "pop %%ebp;"
#define sysc_int_1 "push %%ebp;" sysc_int_0 "pop %%ebp;"
#define sysc_int_2 "push %%esi;" sysc_int_1 "pop %%esi;"
#define sysc_int_3 "push %%edi;" sysc_int_2 "pop %%edi;"
#define sysc_int_4 "push %%ebx;" sysc_int_3 "pop %%ebx;"
#define sysc_recv_1(dx) "=d" (dx)
#define sysc_recv_2(dx, bx) sysc_recv_1(dx), "=b" (bx)
#define sysc_recv_3(dx, bx, di) sysc_recv_2(dx, bx), "=D" (di)
#define sysc_recv_4(dx, bx, di, si) sysc_recv_3(dx, bx, di), "=S" (si)
#define sysc_send_1(dx) "d" (dx),
#define sysc_send_2(dx, bx) sysc_send_1(dx) "b" (bx),
#define sysc_send_3(dx, bx, di) sysc_send_2(dx, bx) "D" (di),
#define sysc_send_4(dx, bx, di, si) sysc_send_3(dx, bx, di) "S" (si),
#define $concat(x, y) x##y
#define $concat3(x, y, z) x##y##z
#define $expand(x) x
#define $nothing
#define mk_syscall(ax, n, ...) \
	asm volatile ($expand($concat(sysc_int_, n)) \
			: __VA_ARGS__, "a" (ax))

#ifndef SYSAPI_STATIC
#define SYSAPI_STATIC static inline
#endif

#define SYS_CALL 0x0000
#define SYS_REPLY 0x0400
#define SYS_WAIT 0x0800
#define SYS_REPLYWAIT 0x0c00
#define SYS_YIELD 0x1000
#define SYS_SETBRK 0x1400
#define SYS_PAGGER 0x1800

SYSAPI_STATIC reg_t sysc_1(wcid_t to, reg_t data)
{
	reg_t res;
	mk_syscall(to, 4, "=c" (res) : "c" (data), "d" (0));
	return res;
}

SYSAPI_STATIC reg_t sysc_1_2(wcid_t to, reg_t data)
{
	reg_t res;
	mk_syscall(to, 4, "=d" (res) : "c" (0), "d" (data));
	return res;
}

SYSAPI_STATIC reg_t sysc_2_r1(wcid_t to, reg_t data1, reg_t data2)
{
	reg_t res;
	mk_syscall(to, 4, "=c" (res) : "c" (data1), "d" (data2));
	return res;
}

SYSAPI_STATIC reg_t sysc_2_r2(wcid_t to, reg_t data1, reg_t data2)
{
	reg_t res;
	mk_syscall(to, 4, "=d" (res) : "c" (data1), "d" (data2));
	return res;
}

SYSAPI_STATIC void sysc_2p(wcid_t to, reg_t *pdata1, reg_t *pdata2)
{
	mk_syscall(to, 4, "=c" (*pdata1), "=d" (*pdata2)
			: "c" (*pdata1), "d" (*pdata2));
}

SYSAPI_STATIC void sysc_3p(wcid_t to, reg_t *pdata1,
		reg_t *pdata2, reg_t *pdata3)
{
	mk_syscall(to, 3, "=c" (*pdata1), "=d" (*pdata2), "=b" (*pdata3)
			: "c" (*pdata1), "d" (*pdata2), "b" (*pdata3));
}

SYSAPI_STATIC void sysc_1v(wcid_t to, const reg_t *snd, reg_t *rcv)
{
	mk_syscall(to, 4, "=c" (rcv[0]) : "c" (snd[0]), "d" (0));
}

SYSAPI_STATIC void sysc_2v(wcid_t to, const reg_t *snd, reg_t *rcv)
{
	mk_syscall(to, 4, "=c" (rcv[0]), "=d" (rcv[1])
			: "c" (snd[0]), "d" (snd[1]));
}

SYSAPI_STATIC void sysc_3v(wcid_t to, const reg_t *snd, reg_t *rcv)
{
	mk_syscall(to, 3, "=c" (rcv[0]), "=d" (rcv[1]), "=b" (rcv[2])
			: "c" (snd[0]), "d" (snd[1]), "b" (snd[2]));
}

SYSAPI_STATIC void sysc_4v(wcid_t to, const reg_t *snd, reg_t *rcv)
{
	mk_syscall(to, 2, "=c" (rcv[0]), "=d" (rcv[1]),
			"=b" (rcv[2]), "=S" (rcv[3]):
			"c" (snd[0]), "d" (snd[1]),
			"b" (snd[2]), "S" (snd[3]));
}

SYSAPI_STATIC void sysc_5v(wcid_t to, const reg_t *snd, reg_t *rcv)
{
	mk_syscall(to, 1, "=c" (rcv[0]), "=d" (rcv[1]), "=b" (rcv[2]),
			"=S" (rcv[3]), "=D" (rcv[4]):
			"c" (snd[0]), "d" (snd[1]), "b" (snd[2]),
			"S" (snd[3]), "D" (snd[4]));
}

#ifdef ENABLE_YIELD_6V
SYSAPI_STATIC void sysc_6v(wcid_t to, const reg_t *snd, reg_t *rcv)
{
	mk_syscall(to, 1br, "=c" (rcv[0]), "=d" (rcv[1]), "=b" (rcv[2]),
			"=S" (rcv[3]), "=D" (rcv[4]), "=r" (rcv[5]):
			"c" (snd[0]), "d" (snd[1]), "b" (snd[2]),
			"S" (snd[3]), "D" (snd[4]), "r" (snd[5]));
}
#endif

#define sysc_nv(n, to, snd, rcv) \
	$expand($concat3(sysc_, n, v)(to, snd, rcv))
