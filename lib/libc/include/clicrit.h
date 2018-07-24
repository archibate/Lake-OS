#pragma once

#include "asm.h"

#define CLI_CRIT_BEGIN(n) \
	unsigned __crit_eflags##n = io_get_eflags(); \
	io_cli();
#define CLI_CRIT_END(n) \
	io_set_eflags(__crit_eflags##n);

//void cli_crit_begin(void);
//void cli_crit_end(void);
