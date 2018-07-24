; vim: ft=nasm ai
[BITS 32]

	extern current
	extern _stktop
	global __asm_int_hand_sys
	global syscl_table
	extern thread_switch
	extern sys_call
	extern sys_reply
	extern sys_wait
	extern sys_replywait
	extern sys_yield
	extern sys_setbrk
	extern sys_pagger
	extern illegal_syscall

[SECTION .rodata]

	alignb 4
syscl_table:
	dd sys_call ; 00
	dd sys_reply ; 04
	dd sys_wait ; 08
	dd sys_replywait ; 0c
	dd sys_yield ; 10
	dd sys_setbrk ; 14
	dd sys_pagger ; 18
	dd illegal_syscall ; 1c

[SECTION .text]

__asm_int_hand_sys:
	push dword 0
	push dword 0
	push gs
	push fs
	push es
	push ds
	pushad
	mov edx, ss
	mov ds, edx
	mov es, edx
	mov esp, _stktop
	mov dl, ah
	and edx, (8-1)*4
	call [syscl_table + edx]
	mov esp, [current]
	popad
	pop ds
	pop es
	pop fs
	pop gs
	add esp, 8
	iretd
