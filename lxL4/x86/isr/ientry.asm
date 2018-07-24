; vim: ft=nasm ai
[BITS 32]

	global asm_int_hret
	global asm_int80_hret
	extern current
	extern _stktop

	global __asm_int_hand_unknown

	global __asm_int_hand_00
	extern int_hand_00

	global __asm_int_hand_06
	extern int_hand_06

	global __asm_int_hand_08
	extern int_hand_08

	global __asm_int_hand_0a
	extern int_hand_0a

	global __asm_int_hand_0b
	extern int_hand_0b

	global __asm_int_hand_0c
	extern int_hand_0c

	global __asm_int_hand_0d
	extern int_hand_0d

	global __asm_int_hand_0e
	extern int_hand_0e

	global __asm_int_hand_20
	extern int_hand_20

	global __asm_int_hand_21
	extern int_hand_21

	global __asm_int_hand_27
	extern int_hand_27

[SECTION .text]

__asm_int_hand_unknown:
	cli
	hlt

__asm_int_hand_00: ;#ZF
	push dword 0
	push int_hand_00
	jmp excp_route

__asm_int_hand_06: ;#UD
	push dword 0
	push int_hand_06
	jmp excp_route

__asm_int_hand_08: ;#DF
	push int_hand_08
	jmp excp_route

__asm_int_hand_0a: ;#TS
	push int_hand_0a
	jmp excp_route

__asm_int_hand_0b: ;#NP
	push int_hand_0b
	jmp excp_route

__asm_int_hand_0c: ;#SS
	push int_hand_0c
	jmp excp_route

__asm_int_hand_0d: ;#GP
	push int_hand_0d
	jmp excp_route

__asm_int_hand_0e: ;#PF
	push int_hand_0e
	jmp excp_route

__asm_int_hand_21:
	push dword 0
	push int_hand_21
	jmp irq_route

__asm_int_hand_27:
	push dword 0
	push int_hand_27
	jmp irq_route

excp_route:
irq_route:
	push gs
	push fs
	push es
	push ds
	pushad
	mov eax, ss
	mov ds, eax
	mov es, eax
	mov eax, esp
	mov esp, _stktop
	push eax ; current(.ctx)
	call [eax + 4 * (8 + 4)] ; ctx.isr_addr
asm_int_hret:
	mov esp, [current]
	popad
	pop ds
	pop es
	pop fs
	pop gs
	add esp, 8
	iretd
