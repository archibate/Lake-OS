#include <x86/gdtidt.h>
#include <string.h>
#include <x86/tss.h>

static void tss32_init(struct tss32 *tss);
static void reflush_tss(void);
static void load_tr(unsigned short sel);

void init_tss(void)
{
	for (int i = 0; i < TSS_NR; i++) {
		tss32_init(_tss + i);
		set_segmdesc(_gdt + 5 + i, 103,
				(reg_t) (_tss + i), AR_TSS32);
	}
	reflush_tss();
}

static void tss32_init(struct tss32 *tss)
{
	extern char _stktop[];
	memset(tss, 0, sizeof(struct tss32));
	tss->ss0 = 0x10;
	tss->esp0 = (reg_t) _stktop;
	tss->eflags = 0x202;
	tss->iomap = 0x40000000;
}

static void reflush_tss(void)
{
	load_tr(5*8);
}

static void load_tr(unsigned short sel)
{
	asm volatile ("ltr %%ax" :: "a" (sel));
}
