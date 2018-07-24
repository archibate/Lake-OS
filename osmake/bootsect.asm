; vim: ft=nasm ai

FDMEM0	equ	0x8000
HEADOFF	equ	0x4400
DRV_NR	equ	0x00
NCYLS	equ	10
SAVCYLS	equ	0xff0

	org 0x7c00

_start:
	jmp entry

        DB        0x90
        DB        "lake-ipl"        ; freeparam 启动区的名称可以是任意的字符串（8字节）
        DW        512                ; 每个扇区（sector）的大小（必须为512字节）
        DB        1                ; 簇（cluster）的大小（必须为1个扇区）
        DW        1                ; FAT的起始位置（一般从第一个扇区开始）
        DB        2                ; FAT的个数（必须为2）
        DW        224                ; 根目录的大小（一般设成224项）
        DW        2880            ; 该磁盘的大小（必须是2880扇区）
        DB        0xf0            ; 磁盘的种类（必须是0xf0）
        DW        9                ; FAT的长度（必须是9扇区）
        DW        18                ; 1个磁道（track）有几个扇区（必须是18）
        DW        2                ; 磁头数（必须是2）
        DD        0                ; 不使用分区，必须是0
        DD        2880            ; 重写一次磁盘大小
        DB        0x00              ; int13h 所用的驱动器号（A软盘为0x00)
	DB	  0x00		    ; 未使用
	DB	  0x29		    ; 扩展引导标记
        DD        0xffffffff        ; 卷序列号
        DB        "LAKE-OS FDA"    ; 卷标（11字节）
        DB        "FAT12   "        ; 磁盘格式（8字节）
        RESB    18                ; 先空出18字节

entry:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, _start

	mov si, msg_load
	call print

readdisk:
	mov ax, FDMEM0 >> 4
	mov es, ax
	mov ch, 0 ; cyln
	mov dh, 0 ; head
	mov cl, 1 ; sect
.loop:
	mov si, 5 ; max_fail_time
.retry:
	mov ah, 0x02
	mov al, 1
	xor bx, bx
	mov dl, DRV_NR
	int 0x13
	jnc .next
	dec si
	jz error
	mov ah, 0x00
	mov dl, DRV_NR
	int 0x13
	jmp .retry
.next:
	mov ax, es
	add ax, 0x0020
	mov es, ax
	inc cl
	cmp cl, 18
	jbe .loop
	mov cl, 1
	inc dh
	cmp dh, 2
	jb .loop
	mov dh, 0
	call putdot
	inc ch
	cmp ch, NCYLS
	jb .loop
.readok:
	mov [SAVCYLS], ch
	mov si, msg_ok
	call print
	jmp FDMEM0 + HEADOFF

error:
	mov si, msg_err
	call print
.waitkey:
	mov ah, 0
	int 0x16
.reset:
	int 0x19

halt:
	hlt
	jmp halt

putdot:
	mov ah, 0x0e
	mov al, '.'
	int 0x10
	ret

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

msg_load:
	db 13, 10, 10
	db "Loading System"
	db 0

msg_ok:
	db "done"
	db 13, 10
	db "Booting kernel..."
	db 0

msg_err:
	db 13, 10
	db "Error Occurred"
	db 13, 10
	db "press any key to reset"
	db 13, 0

	resb $$ + 510 - $
	db 0x55, 0xaa
