#pragma once

#include <reg_t.h>

typedef struct ctx {
	union {
		reg_t gr[8]; // 8
		struct {
			reg_t di, si, bp, usp, bx;
			union {
				struct {
					reg_t dx, cx;
				};
				struct {
					reg_t sv_pf_offset, sv_pf_errcd;
				};
				struct {
					reg_t sv_buff, sv_mask;
				};
			};
			reg_t ax;
		};
	};
	union {
		reg_t sr[4]; // 12
		struct {
			reg_t ds, es, fs, gs;
		};
	};
	union {
		struct {
			reg_t isr_addr, errcd; // 14
		};
		struct {
			reg_t pf_addr, pf_errcd;
		};
		struct {
			reg_t pf2_vir, pf2_pte;
		};
	};
	reg_t ip, cs, eflags; // 17
	reg_t sp, ss; // 19
} ctx_t;

void dump_context(const ctx_t *ctx);
#define is_kernel_context(ctx) (((ctx)->cs & 0x3) == 0)
void context_init(ctx_t *ctx, reg_t ip, reg_t sp, reg_t eflags);
void kernel_context_init(ctx_t *ctx, reg_t ip, reg_t sp, reg_t eflags);
