#pragma once

#include <reg_t.h>

struct tss32 {
    reg_t backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;
    reg_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
    reg_t es, cs, ss, ds, fs, gs;
    reg_t ldtr, iomap;
};

#define TSS_NR 1

extern struct tss32 _tss[TSS_NR];

static void set_tss0_esp0(reg_t esp0)
{
	_tss[0].esp0 = esp0;
}
