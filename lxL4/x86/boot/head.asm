; vim: ft=nasm ai

FDMEM0	equ	0x8000
FDMEM	equ	0x100000
HEADOFF	equ	0x4400
KERHDIS	equ	512*6
KERNOFF	equ	HEADOFF + KERHDIS
KERNBEG	equ	FDMEM0 + KERNOFF
SAVCYLS	equ	0xff0

	org FDMEM0 + HEADOFF

_start:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, _start

	mov ah, 0x01
	mov ch, 5
	mov cl, 6
	int 0x10

setup_32:
	mov al, 0xff
	out 0x21, al
	nop
	out 0xa1, al
	cli

	call waitkbc
	mov al, 0xd1
	out 0x64, al
	call waitkbc
	mov al, 0xdf
	out 0x60, al
	call waitkbc

	lgdt [GDTR0]
	mov eax, cr0
	and eax, 0x7fffffff
	or eax, 0x00000001
	mov cr0, eax
	jmp pipflush

waitkbc:
	in al, 0x64
	test al, 0x02
	jnz waitkbc
	ret

	alignb 16
GDT0:
	dw 0x0000, 0x0000
	db 0x00, 0x00, 0x00, 0x00
	dw 0xffff, 0x0000
	db 0x00, 0x9a, 0xcf, 0x00
	dw 0xffff, 0x0000
	db 0x00, 0x92, 0xcf, 0x00
GDTR0:
	dw $-GDT0-1
	dd GDT0
IDTR0:
	dw 0
	dd 0

pipflush:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov sp, _start

copyfdmem:
	mov esi, FDMEM0
	mov edi, FDMEM
	xor ecx, ecx
	mov cl, [SAVCYLS]
	test cl, cl
	imul ecx, 512 * 18 * 2 / 4
	call memcpy
	jmp dword 0x8 : beg32

memcpy:
        MOV        EAX,[ESI]
        ADD        ESI,4
        MOV        [EDI],EAX
        ADD        EDI,4
        SUB        ECX,1
        JNZ        memcpy            ; 引き算した結果が0でなければmemcpyへ
        RET

[BITS 32]

	alignb 4
TSTOFF:
	dd 0xcafebabe
beg32:  ; check if A20 were enabled
	mov ecx, [TSTOFF]
	mov eax, [0x10000 + TSTOFF]
	xor eax, 0xdeadbeaf
	mov [TSTOFF], eax
	cmp eax, [0x10000 + TSTOFF]
	je beg32
	mov [TSTOFF], ecx
	jmp KERNBEG
halt:
	hlt
	jmp halt

	resb KERHDIS + ($$-$)
