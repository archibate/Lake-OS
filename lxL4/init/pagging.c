#include <dma.h>
#include <asm.h>

static void setup_pagging(void);
static void enable_pagging(void);

void init_pagging(void)
{
	setup_pagging();
	enable_pagging();
}

static void setup_pagging(void)
{
	unsigned attr = PG_P | PG_W | PG_G | PG_U;//TODO
	for (int i = 0; i < DMA_PGTS; i++) {
		ad_t ad = (ad_t) (_ptes + 1024 * i);
		_pgd[i] = ad | attr;
	}

	for (int i = 0; i < DMA_PAGES; i++) {
		ad_t ad = 4096 * i;
		_ptes[i] = ad | attr;
	}
}

#define CR0_PG  0x80000000
#define CR4_PGE 0x00000080

static void enable_pagging(void)
{
	//unsigned long cr4 = io_get_cr4();
	//cr4 |= CR4_PGE;
	//io_set_cr4(cr4);
	io_set_cr3((unsigned long) _pgd);
	unsigned long cr0 = io_get_cr0();
	cr0 |= CR0_PG;
	io_set_cr0(cr0);
}
