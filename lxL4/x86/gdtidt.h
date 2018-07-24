#pragma once

#include "desc.h"

#define GDT_NR 6
#define IDT_NR 256

extern struct segmdesc _gdt[GDT_NR];
extern struct gatedesc _idt[IDT_NR];
