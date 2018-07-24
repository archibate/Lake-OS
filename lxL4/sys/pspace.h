#pragma once

#include "pagger.h"

#define MAX_PAGGERS 32
#define PGRIDMASK (MAX_PAGGERS - 1)

typedef struct pspace {
	pagger_info_t pgrs[MAX_PAGGERS];
} pspace_t;
