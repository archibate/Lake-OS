#include <sys/thread.h>
#include <debug.h>
#include <panic.h>
#include <asm.h>

static void tick_callback(void)
{
	if (current->rest-- <= 0) {
		extern void sys_yield(void);
		sys_yield();
	}
}

void int_hand_20(void)
{
	io_outb(0x20, 0x60);

	//printstr("t");
		//printint((reg_t) (idle_thr.state));
	//printstr(";");
	static int tick;
	if (tick > 100)
		panic("out of time!");
#if 0
	printstr("\Ec\x0aint_hand_20: tick = ");
	printint(tick);
	printstr("\n\Ec\x07");
#endif

	tick_callback();

	tick++;
}
