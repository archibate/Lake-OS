#include <mm/vspace.h>
#include <mm/vsctl.h>
#include <debug.h>
#include <assert.h>

void do_test2(void)
{
	vspace_t vs;
	vspace_init(&vs);
	vspace_switch(&vs);
	v_map(0x20000000,0x2000,PG_W);*((volatile
	int*)0x20000000)=23;assert(*((volatile
	int*)0x2000)==23);v_unmap(0x20000000);
}
