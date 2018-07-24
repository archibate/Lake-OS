#pragma once

#include "page.h"

#define USR_KERN_SEP 0x800000 // should be same as in memlay.h
#define USR_CODE_BEG 0x10000000
#define USR_STACK_END 0xf0000000
#define USR_STACK_PAGES 0x10000
#define USR_STACK_SIZE (USR_STACK_PAGES * PGSIZE)
#define USR_STACK_BEG (USR_STACK_END - USR_STACK_SIZE) // 0xe0000000
