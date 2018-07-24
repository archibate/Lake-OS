; vim: ft=nasm ai
[BITS 32]

	global asm_segment_regs_flush

[SECTION .text]

asm_segment_regs_flush:
	mov eax, 0x10
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	mov ss, eax
	pop eax
	push dword 0x08
	push eax
	retf
