; vim: ft=nasm ai
[BITS 32]

	global _start
	extern main

[SECTION .text.startup]
_start:
	call main
again: ; TODO: usr exit() instread
	mov eax, 0x1000
	int 0x67
	jmp again
