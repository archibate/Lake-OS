ENTRY(_start);

SECTIONS {
	. = 0xd000;
	PROVIDE(_kbeg = .);
	PROVIDE(_binfo = . - 12);

	.text : {
		*(.text)
		*(.rdata)
		*(.rodata)
		. = ALIGN(4096);
	}

	.data : {
		*(.data)
		*(.sdata)
		. = ALIGN(4096);
	}

	.bss : {
		*(.bss)
		*(.sbss)
		*(COMMON)
		. = ALIGN(4096);
	}

	PROVIDE(_idt = 0x8000);
	PROVIDE(_gdt = 0x8800);
	PROVIDE(_tss = 0x8b00);
	PROVIDE(_pgd = 0x9000);
	PROVIDE(_stktop = 0x9f000);
	PROVIDE(_fdbuf = 0x100000);
	PROVIDE(_ptes = 0x268000);

	/DISCARD/ : {
		*(.interp)
		*(.note*)
		*(.gnu*)
		*(.GNU*)
		*(.dyn*)
	}
}
