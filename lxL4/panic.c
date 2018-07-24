#include "tty.h"
#include "asm.h"

extern struct tty_ctl tty0;

void panic(const char *str)
{
	tty0.fgcolor = 0xcf00;
	tty_putstr(&tty0, "\nPANIC: ");
	tty_putstr(&tty0, str);
	tty_putstr(&tty0, "\n");
	io_clihlt();
}
