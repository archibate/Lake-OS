#include <sys/context.h>
#include <debug.h>

void dump_context(const ctx_t *ctx)
{
	printstr("errcd=");
	printint(ctx->errcd);
	printstr("\necx=");
	printint(ctx->cx);
	printstr("\nedx=");
	printint(ctx->dx);
	printstr("\neflags=");
	printint(ctx->eflags);
	printstr("\ncs:eip=");
	printint(ctx->cs);
	printstr(":");
	printint(ctx->ip);
	printstr("\nss:esp=");
	printint(ctx->ss);
	printstr(":");
	printint(ctx->sp);
	printstr("\n");
}
