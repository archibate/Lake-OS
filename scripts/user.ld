ENTRY(_start);

SECTIONS {
	. = 0x10000000;

	.text : {
		*(.text.startup)
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

	/DISCARD/ : {
		*(.interp)
		*(.note*)
		*(.gnu*)
		*(.GNU*)
		*(.dyn*)
	}
}
