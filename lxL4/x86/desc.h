#pragma once

#include <ad_t.h>

struct segmdesc {
	short limit_low, base_low;
	char base_mid, access_right;
	char limit_high, base_high;
};
struct gatedesc {
	short offset_low, selector;
	char dw_count, access_right;
	short offset_high;
};

#define AR_DPL_3	0x0060
#define AR_DATA32_RW	0x4092
#define AR_CODE32_ER	0x409a
#define AR_INTGATE32	0x008e
#define AR_TSS32	0x0089

void set_segmdesc(struct segmdesc *sd,
		unsigned limit, ad_t base, int ar);
void set_gatedesc(struct gatedesc *gd,
		int offset, int selector, int ar);
