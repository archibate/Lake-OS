#pragma once

#include "sizet.h"

#define offsetof(type, member) \
	((size_t) ((type*) 0)->member)
