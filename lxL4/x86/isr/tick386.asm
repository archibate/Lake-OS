; vim: ft=nasm ai
[BITS 32]

	extern current
	extern _stktop
	global __asm_int_hand_20
	extern int_hand_20

[SECTION .text]

__asm_int_hand_20:
	sub esp, 8
	push gs
	push fs
	push es
	push ds
	pushad
	mov esp, _stktop
	mov eax, ss
	mov ds, eax
	mov es, eax
	call int_hand_20
	mov esp, [current]
	popad
	pop ds
	pop es
	pop fs
	pop gs
	add esp, 8
	iretd
