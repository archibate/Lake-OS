#include <x86/gdtidt.h>
#include <sysapi.h> // well, SYSCALL_INT_NR
#include <asm.h>

static void load_gdtr(unsigned short limit, ad_t base);
static void load_idtr(unsigned short limit, ad_t base);

extern void asm_segment_regs_flush(void);

void init_gdtidt(void)
{
	/* GDT的初始化 */
	for (int i = 0; i < GDT_NR; i++) {
		set_segmdesc(_gdt + i, 0, 0, 0);
	}
	/* GDT的设定 */
	set_segmdesc(_gdt + 1, 0xffffffff, 0x00000000, AR_CODE32_ER);
	set_segmdesc(_gdt + 2, 0xffffffff, 0x00000000, AR_DATA32_RW);
	set_segmdesc(_gdt + 3, 0xffffffff, 0x00000000, AR_CODE32_ER + AR_DPL_3);
	set_segmdesc(_gdt + 4, 0xffffffff, 0x00000000, AR_DATA32_RW + AR_DPL_3);

	load_gdtr(GDT_NR*8-1, (ad_t) _gdt);
	asm_segment_regs_flush();

	/* IDT的初始化 */
	for (int i = 0; i < IDT_NR; i++) {
		extern void __asm_int_hand_unknown(void);
		set_gatedesc(_idt + i, (ad_t) __asm_int_hand_unknown,
			0x08, AR_INTGATE32);
		//set_gatedesc(_idt + i, 0, 0, 0);
	}
	/* IDT的设定 */
	extern void __asm_int_hand_00(void);
	set_gatedesc(_idt + 0x00, (ad_t) __asm_int_hand_00,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_06(void);
	set_gatedesc(_idt + 0x06, (ad_t) __asm_int_hand_06,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_08(void);
	set_gatedesc(_idt + 0x08, (ad_t) __asm_int_hand_08,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_0a(void);
	set_gatedesc(_idt + 0x0a, (ad_t) __asm_int_hand_0a,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_0b(void);
	set_gatedesc(_idt + 0x0b, (ad_t) __asm_int_hand_0b,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_0c(void);
	set_gatedesc(_idt + 0x0c, (ad_t) __asm_int_hand_0c,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_0d(void);
	set_gatedesc(_idt + 0x0d, (ad_t) __asm_int_hand_0d,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_0e(void);
	set_gatedesc(_idt + 0x0e, (ad_t) __asm_int_hand_0e,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_20(void);
	set_gatedesc(_idt + 0x20, (ad_t) __asm_int_hand_20,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_21(void);
	set_gatedesc(_idt + 0x21, (ad_t) __asm_int_hand_21,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_27(void);
	set_gatedesc(_idt + 0x27, (ad_t) __asm_int_hand_27,
			0x08, AR_INTGATE32);
	extern void __asm_int_hand_sys(void);
	set_gatedesc(_idt + SYSCALL_INT_NR, (ad_t) __asm_int_hand_sys,
			0x08, AR_INTGATE32 + AR_DPL_3);

	load_idtr(IDT_NR*8-1, (ad_t) _idt);

	return;
}

static void load_gdtr(unsigned short limit, ad_t base)
{
	struct {
		unsigned short limit;
		ad_t base;
	} __attribute__((packed)) gdtr = { limit, base };
	asm volatile ("lgdt %0" :: "m" (gdtr));
}

static void load_idtr(unsigned short limit, ad_t base)
{
	struct {
		unsigned short limit;
		ad_t base;
	} __attribute__((packed)) idtr = { limit, base };
	asm volatile ("lidt %0" :: "m" (idtr));
}
