OBJDIR=obj
BINDIR=bin
SRCDIR=.
INCDIR=.
ROTDIR=../..
include $(ROTDIR)/Makefile.dirs
include $(ROTDIR)/Makefile.odirs

ARLIB=$(BINDIR)/lib.a

PHONY+=all
all: arlib

include $(MAKPREFIX)usual
include $(MAKPREFIX)library

PHONY+=arlib
arlib: $(ARLIB)

include $(MAKPREFIX)ending
