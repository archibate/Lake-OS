#pragma once

struct tcb;
typedef struct pagger_info {
	ad_t beg;
	ad_t end;
	struct tcb *server;
} pagger_info_t;

#include "tcb.h"
