#include <sys/uthread.h>
#include <debug.h>
#include "initrdap.h"

tcb_t initrd_thrs[INITRD_APPS];

void init_initrdap(void)
{
	printstr("\ninitrdaps:\n");
	for (int i = 0; i < INITRD_APPS; i++) {
		ucode_t code;
		code.data = initrd_apps[i];
		code.size = initrd_apps[i+1] - code.data;
		printstr("\t addr=0x");
		printint((reg_t) code.data);
		printstr(", size=0x");
		printint((reg_t) code.size);
		printstr("\n");
		uthread_run(&initrd_thrs[i], &code);
		initrd_thrs[i-1].next = &initrd_thrs[i];
	}
	printstr("\n");
	initrd_thrs[INITRD_APPS-1].next = &initrd_thrs[0];
}
