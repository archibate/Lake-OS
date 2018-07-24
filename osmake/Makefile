# vim: ft=make
OBJDIR=obj
BINDIR=bin
SRCDIR=.
ROTDIR=..
include $(ROTDIR)/Makefile.dirs
include $(ROTDIR)/Makefile.odirs
IMAGE=$(KRNDIR)/bin/lxL4.sys
FDIMAGE=$(BINDIR)/floppy.img
BOOTSECT=$(BINDIR)/bootsect.bin
FDFAT0=$(BINDIR)/fdfat0.bin
WELCM=$(RESDIR)/lkoswlcm.txt
USHEL=$(RESDIR)/ustest.com
QEMUFLAGS=-hda $(RESDIR)/testhd.img
MNTDIR=files


PHONY+=default
default: fdimage

NOOBJ=1
include $(MAKPREFIX)usual
include Makefile.run
include Makefile.floppy

PHONY+=fdimage
fdimage: $(FDIMAGE)

include $(MAKPREFIX)clean
