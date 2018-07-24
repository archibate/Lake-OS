#include <lxL4/sysipc.h>
#include <lxL4/sysmm.h>
#include <lxL4/fault.h>
#include <lxL4/page.h>
#include <string.h>
#include <ad_t.h>
#include <rand.h>
#include <pgalloc.h>
#include "ata.h"

static void load_data(char *buff, size_t offset)
{
	memset(buff, 1, PGSIZE);
	lba_t lba = offset / SECTSIZE;
	ata_rwsects(ATA_MASTER, ATA_READ, buff, lba, PGSIZE / SECTSIZE);
}

void fault_server(void)
{
	L4m_fault_info_t u;
	L4m_fault_result_t r;

	L4_Wait(2, &u.data);
	while (1) {
		ad_t offset = u.pf_offset & PGMASK;

		if (!(u.pf_errcd & PG_W)) {
			ad_t buff = alloc_page();
			load_data((char *) buff, offset);
			r.sv_buff = buff;
			r.sv_mask = PG_W;
		} else {
			// unasdasd
			asm volatile("cli;hlt");
		}

		L4_ReplyWait(2, &r.data, &u.data);
	}
}
