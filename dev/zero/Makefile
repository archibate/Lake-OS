OBJDIR=obj
BINDIR=bin
SRCDIR=.
INCDIR=.
ROTDIR=../..
include $(ROTDIR)/Makefile.dirs
include $(ROTDIR)/Makefile.odirs

BINIMG=$(BINDIR)/zero.com
ELFIMG=$(BINDIR)/zero.elf
LDSCRIPT=$(SCRDIR)/user.ld
LIBS=libc libsys libheap

PHONY+=default
default: binimg

include $(MAKPREFIX)usual
include $(MAKPREFIX)link
include $(MAKPREFIX)image

PHONY+=binimg
binimg: $(BINIMG)

PHONY+=elfimg
elfimg: $(ELFIMG)

include $(MAKPREFIX)ending
