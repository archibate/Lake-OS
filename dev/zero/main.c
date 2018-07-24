#include <lxL4/sysipc.h>
#include <lxL4/sysmm.h>
#include <lxL4/fault.h>
#include <lxL4/page.h>
#include <string.h>
#include <ad_t.h>
#include <rand.h>
#include <pgalloc.h>

void load_data(char *data, size_t offset)
{
	memset(data, 0, PGSIZE);
}

void fault_server(void)
{
	L4m_fault_info_t u;
	L4m_fault_result_t r;

	L4_Wait(2, &u.data);
	while (1) {
		ad_t offset = u.pf_offset & PGMASK;
		ad_t buff = alloc_page();
		load_data((char *) buff, offset);
		r.sv_buff = buff;

		L4_ReplyWait(2, &r.data, &u.data);
	}
}

int main(void)
{
	fault_server();
}
