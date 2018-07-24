#pragma once

#include "likely.h"

#define __assertion_failed() /* TODO! */ \
	asm volatile ("cli; hlt" :: "d" (0xdeadc0de));

#define assert(x) do { \
       	if unlikely(!(x)) { \
		__assertion_failed(); \
		__builtin_unreachable(); \
       	} \
} while (0)
