#pragma once

#include "reg_t.h"
#include "sysapi.h"

#if 0
#define L4x_Setcap(id, subid, myid) sysc_2_r1(SYS_SETCAP | (id), subid, myid)
#define L4x_Getcap(id, subid, myid) sysc_2_r1(SYS_GETCAP | (id), subid, myid)
#endif
#define L4_Call1(to, data) sysc_1(SYS_CALL | (to), data)
#define L4_Reply1(res) sysc_1(SYS_REPLY, res)
#define L4_ReplyWait1(res) sysc_1(SYS_REPLYWAIT, res)
#define L4_Wait1() sysc_1(SYS_WAIT, 0x5a17)
#define L4_Yield() sysc_1(SYS_YIELD, 0xebfe)
static reg_t __$_zero6[6], __$_nwrb6[6];
#define L4_Call(n, to, res, data) sysc_nv(n, SYS_CALL | (to), (const reg_t *) (data), (reg_t *) (res))
#define L4_Reply(n, res) sysc_nv(n, SYS_REPLY, (const reg_t *) (res) __$_nwrb6)
#define L4_ReplyWait(n, res, data) sysc_nv(n, SYS_REPLYWAIT, (const reg_t *) (res), (reg_t *) (data))
#define L4_Wait(n, data) sysc_nv(n, SYS_WAIT, __$_zero6, (reg_t *) (data))
