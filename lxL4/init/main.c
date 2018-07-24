#include "inits.h"
#include <debug.h>
#include <panic.h>
#include <asm.h>

static void __attribute__((noreturn)) cpu_idle(void);
int __attribute__((noreturn)) _main(void)
{
	init_tty0();
	printstr("done\n");
	init_gdtidt();
	init_tss();
	init_pic();
	init_pagging();
	init_ppm();
	init_idle();
	init_initrdap();
	init_timer(1000);

	extern void do_test(void);
	extern void do_test2(void);
	do_test2();
	do_test();

	io_outb(0x21, 0xf8);
	io_outb(0xa1, 0xff);

	extern void __attribute__((noreturn)) asm_int_hret();
	asm_int_hret();
}
