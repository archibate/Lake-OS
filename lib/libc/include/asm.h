#pragma once

static inline void io_sti(void)
{
	asm volatile("sti");
}

static inline void io_cli(void)
{
	asm volatile("cli");
}

static inline void io_hlt(void)
{
	asm volatile("hlt");
}

static inline void io_stihlt(void)
{
	asm volatile("sti;hlt");
}

static inline void __attribute__((noreturn)) io_clihlt(void)
{
	asm volatile("cli;hlt");
	__builtin_unreachable();
}

static inline void io_outb(int port, unsigned char data)
{
	asm volatile("outb %%al, %%dx" :: "a" (data), "d" (port));
}

static inline unsigned char io_inb(int port)
{
	unsigned char data;
	asm volatile("inb %%dx, %%al" : "=a" (data) : "d" (port));
	return data;
}

// see https://github.com/Clann24/jos/blob/master/lab1/code/inc/x86.h
static inline void io_outsl(int port, const void *buf, unsigned long count)
{
	asm volatile("cld;repnz;outsl"
			: "=S" (buf), "=c" (count)
			: "d" (port), "0" (buf), "1" (count));
}

static inline void io_insl(int port, void *buf, unsigned long count)
{
	asm volatile("cld;repnz;insl"
			: "=D" (buf), "=c" (count)
			: "d" (port), "0" (buf), "1" (count));
}

static inline unsigned int io_get_eflags(void)
{
	unsigned int eflags;
	asm volatile("pushfl;pop %%eax" : "=a" (eflags));
	return eflags;
}

static inline void io_set_eflags(unsigned int eflags)
{
	asm volatile("push %%eax;popfl" :: "a" (eflags));
}

static inline void io_invlpg(unsigned long vir)
{
	asm volatile("invlpg (%%eax)" :: "a" (vir));
}

static inline unsigned long long io_rdmsr(unsigned adr)
{
	unsigned eax, edx;
	asm volatile("rdmsr" : "=a" (eax), "=d" (edx) : "c" (adr));
	unsigned long long res = edx;
	res <<= 32;
	res |= eax;
	return res;
}

static inline void io_wrmsr(unsigned adr, unsigned long long val)
{
	unsigned eax = val & 0xffffffff;
	unsigned edx = (val >> 32) & 0xffffffff;
	asm volatile("rdmsr" :: "a" (eax), "d" (edx), "c" (adr));
}

#define _DEF_GET_SET_CRX(crx) \
static inline unsigned long io_get_##crx(void) \
{ \
	unsigned int crx; \
	asm volatile("mov %%"#crx", %%eax" : "=a" (crx)); \
	return crx; \
} \
 \
static inline void io_set_##crx(unsigned int crx) \
{ \
	asm volatile("mov %%eax, %%"#crx :: "a" (crx)); \
}

_DEF_GET_SET_CRX(cr0)
_DEF_GET_SET_CRX(cr2)
_DEF_GET_SET_CRX(cr3)
_DEF_GET_SET_CRX(cr4)
