#pragma once

#include <ad_t.h>

struct tcb;
typedef union cap {
	ad_t addr;
	struct tcb *tcb;
} cap_t;
