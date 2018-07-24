#include <lxL4/umemlay.h>
#include <lxL4/sysipc.h>
#include <lxL4/sysmm.h>
#include <lxL4/fault.h>
#include <lxL4/page.h>
#include <string.h>
#include <assert.h>
#include <ad_t.h>

void load_data(char *data)
{
	memset(data, 0x23, PGSIZE);
}

ad_t brk = USR_STACK_BEG;

ad_t alloc_page(void)
{
	brk += PGSIZE;
	int res = L4m_Setbrk(brk);
	assert(!res);
	return brk - PGSIZE;
}

int main(void)
{
	L4m_fault_info_t u;
	L4m_fault_result_t r;

	L4_Wait(2, &u.data);
	while (1) {
		ad_t buff = alloc_page();
		load_data((char *) buff);
		r.sv_buff = buff;

		L4_ReplyWait(2, &r.data, &u.data);
	}
}
