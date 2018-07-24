; vim: ft=nasm ai
; TODO: uncompleted!

FDMEM0	equ	0x8000
HEADOFF	equ	0x4400
DRV_NR	equ	0x00
SAVCYLS	equ	0xff0

	org 0x100

[SECTION .text]

entry:
	lea si, [msg_load]
	call print

readkern:
	lea dx, [sysfilepath]
	mov ax, 0x3d02
	int 0x21
	jc error
	mov bx, ax
	mov cx, 0xfe00
	lea dx, [buf]
	mov ah, 0x3f
	push bx
	int 0x21
	jc error
	pop bx
	mov ah, 0x3e
	int 0x21
	jc error

readok:
	mov byte [SAVCYLS], 0
	lea si, [msg_ok]
	call print
	lea si, [buf]
	cli
	xor ax, ax
	mov es, ax
	mov di, FDMEM0 + HEADOFF
	mov cx, 0x8000
memcpy:
        MOV        AX,[DS:SI]
        ADD        SI,2
        MOV        [ES:DI],AX
        ADD        DI,2
        SUB        CX,1
        JNZ        memcpy            ; 引き算した結果が0でなければmemcpyへ
	jmp 0x0: FDMEM0 + HEADOFF

error:
	lea si, [msg_err]
	call print
exit:
	int 0x20
	jmp $

print:
	mov ah, 0x0e
.loop:
	lodsb
	test al, al
	jz .fin
	int 0x10
	jmp .loop
.fin:
	ret

[SECTION .data]

msg_load:
	db 13, 10, 10
	db "Loading System..."
	db 0

msg_ok:
	db "done"
	db 13, 10
	db "Booting kernel..."
	db 0

msg_err:
	db 13, 10
	db "Error Occurred"
	db 13, 10, 0

sysfilepath:
	db "LKOSKRNL.SYS", 0

[SECTION .bss]
	alignb 512
buf:
