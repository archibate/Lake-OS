OBJDIR=obj
BINDIR=bin
SRCDIR=.
INCDIR=.
ROTDIR=..
include $(ROTDIR)/Makefile.dirs
include $(ROTDIR)/Makefile.odirs
KSCRDIR=$(KRNDIR)/scripts

IMAGE=$(BINDIR)/lxL4.sys
HEADBIN=$(BINDIR)/x86/boot/head.bin
BINIMG=$(BINDIR)/kernel.bin
ELFIMG=$(BINDIR)/kernel.elf
LDSCRIPT=$(KSCRDIR)/kernel.ld
LIBS=libc

PHONY+=default
default: image

PHONY+=run
run:
	make -C $(ROTDIR) $@

include $(MAKPREFIX)usual
include $(MAKPREFIX)link
include $(MAKPREFIX)image

PHONY+=image
image: $(IMAGE)

PHONY+=binimg
binimg: $(BINIMG)

PHONY+=elfimg
elfimg: $(ELFIMG)

include $(MAKPREFIX)ending
