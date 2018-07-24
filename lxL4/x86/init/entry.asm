; vim: ft=nasm ai
[BITS 32]

	extern _main
	extern _stktop
	global _start

[SECTION .text]        ; 目标文件中写了这些后再写程序

_start:
	cli

	mov eax, cr0
	and eax, 0x1
	or eax, 0x2
	mov cr0, eax
check_x87:
	fninit
	fstsw ax
	test al, al
	jz .pm287
	mov eax, cr0
	xor eax, 0x6
	mov cr0, eax
	jmp .ok
.pm287:	fsetpm
.ok:

	mov esp, _stktop
	xor ebp, ebp

	call _main
halt:
	hlt
	jmp halt
