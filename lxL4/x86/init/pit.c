#include <asm.h>

void init_timer(unsigned int freq)
{
	unsigned int divisor = 1193180 / freq;
	unsigned char lo = divisor & 0xff;
	unsigned char hi = (divisor >> 8) & 0xff;

	io_outb(0x43, 0x36);
	io_outb(0x40, lo);
	io_outb(0x40, hi);
}
