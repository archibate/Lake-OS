#pragma once

#include "thread.h"
#include <sizet.h>

typedef struct ucode {
	const void *data;
	size_t size;
} ucode_t;

void uthread_run(tcb_t *thr, const ucode_t *code);
