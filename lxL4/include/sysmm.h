#pragma once

#include "reg_t.h"
#include "sysapi.h"

#define L4m_Setbrk(brk) sysc_1(SYS_SETBRK, brk)
#define L4m_Pagger(id, pgrid, beg, end) \
	sysc_2_r1(SYS_PAGGER | (id) | ((pgrid) << 16), beg, end)
