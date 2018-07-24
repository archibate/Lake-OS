#include "context.h"
#include <string.h>

void context_init(ctx_t *ctx, reg_t ip, reg_t sp, reg_t eflags)
{
	memset(&ctx->gr, 0, sizeof(ctx->gr));

	for (int i = 0; i < 4; i++)
		ctx->sr[i] = 0x23;

	ctx->ip = ip;
	ctx->sp = sp;
	ctx->cs = 0x1b;
	ctx->ss = 0x23;
	ctx->eflags = eflags;
}

void kernel_context_init(ctx_t *ctx, reg_t ip, reg_t sp, reg_t eflags)
{
	memset(&ctx->gr, 0, sizeof(ctx->gr));
	for (int i = 0; i < 4; i++)
		ctx->sr[i] = 0x10;

	ctx->ip = ip;
	ctx->sp = sp;
	ctx->cs = 0x08;
	ctx->ss = 0x10;
	ctx->eflags = eflags;
}
