
	ORG     0x7c00

        JMP        entry
        DB        0x90
        DB        "NO BOOTS"        ; freeparam 启动区的名称可以是任意的字符串（8字节）
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
        DB        0x00              ; int13h 所用的驱动器号（A软盘为0x00)
	DB	  0x00		    ; 未使用
	DB	  0x29		    ; 扩展引导标记
        DD        0xffffffff        ; 卷序列号
        DB        "           "    ; 卷标（11字节）
        DB        "FAT12   "        ; 磁盘格式（8字节）
        RESB    18                ; 先空出18字节

entry:

        XOR        AX,AX            ; 初始化寄存器
        MOV        DS,AX

        MOV        SI,msg

putloop:
	LODSB
        TEST       AL,AL
        JZ         fin
        MOV        AH,0x0e          ; 显示一个文字
        MOV        BX,15            ; 指定字符颜色
        INT        0x10             ; 调用显卡BIOS
        JMP        putloop
fin:
	MOV	  AH,0x00
	INT	  0x16
	INT	  0x19

msg:
	DB        0x0d, 0x0a, 0x0a
	DB	  "Sorry, This is not a bootable disk."
	DB	  0x0d, 0x0a
	DB	  "press any key to reset"
	DB	  0x0a, 0x00

        RESB    $$ + 510 - $        ; 填写0x00，直到0x001fe

        DB        0x55, 0xaa

; 以下是启动区以外部分的输出

        DB        0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
        RESB    4600
        DB        0xf0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00
        RESB    1469432
