#include "tty.h"

struct tty_ctl tty0;

void init_tty0(void)
{
	tty_init(&tty0, (tty_data_t *) 0xb8000, 80, 25);
}
