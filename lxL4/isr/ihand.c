#include <sys/context.h>
#include <debug.h>
#include <panic.h>
#include <asm.h>

void int_hand_00(ctx_t *ctx)
{
	dump_context(ctx);
	panic("int_hand_00 #ZF!");
}

void int_hand_06(ctx_t *ctx)
{
	dump_context(ctx);
	panic("int_hand_06 #UD!");
}

void int_hand_08(ctx_t *ctx)
{
	dump_context(ctx);
	panic("int_hand_08 #DF!");
}

void int_hand_0a(ctx_t *ctx)
{
	dump_context(ctx);
	panic("int_hand_0a #TS!");
}

void int_hand_0b(ctx_t *ctx)
{
	dump_context(ctx);
	panic("int_hand_0b #NP!");
}

void int_hand_0c(ctx_t *ctx)
{
	dump_context(ctx);
	panic("int_hand_0c #SS!");
}

void int_hand_0d(ctx_t *ctx)
{
	dump_context(ctx);
	panic("int_hand_0d #GP!");
}

void int_hand_21(ctx_t *ctx)
{
	io_outb(0x20, 0x61);

	unsigned char data = io_inb(0x60);
	printstr("int_hand_21: data = 0x");
	printint(data);
	printstr("\n");
}

void int_hand_27(ctx_t *ctx)
/* PIC0©çÌs®SèÝÎô */
/* Athlon64X2@ÈÇÅÍ`bvZbgÌsÉæèPICÌú»É±ÌèÝª1x¾¯¨±é */
/* ±ÌèÝÖÍA»ÌèÝÉÎµÄ½àµÈ¢Åâèß²· */
/* Èº½àµÈ­Ä¢¢ÌH
	¨  ±ÌèÝÍPICú»ÌdCIÈmCYÉæÁÄ­¶µ½àÌÈÌÅA
		Ü¶ßÉ½©µÄâéKvªÈ¢B									*/
{
	io_outb(0x20, 0x67); /* IRQ-07ót®¹ðPICÉÊm(7-1QÆ) */
}
