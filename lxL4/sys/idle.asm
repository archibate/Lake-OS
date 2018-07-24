; vim: ft=nasm ai
[BITS 32]

	global cpu_idle

[SECTION .text]

cpu_idle:
	hlt
	jmp cpu_idle
