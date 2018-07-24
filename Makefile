#!/usr/bin/make -f
#
# - Makefile for Lake-OS
#
#   I believe that perfect comes from details
#
#
ROTDIR=.
include $(ROTDIR)/Makefile.dirs
include $(ROTDIR)/Makefile.odirs

PHONY+=run
run: osall
	make -C $(ROTDIR)/osmake $@

PHONY+=osmake
osmake: osall
	make -C $(ROTDIR)/$@

PHONY+=osall
osall: lxL4

PHONY+=lxL4
lxL4: lib/libc usr/wtest usr/mtest dev/zero dev/rand dev/fd0 dev/ata
	make -C $(ROTDIR)/$@

PHONY+=lib/libc
lib/libc:
	make -C $(ROTDIR)/$@

PHONY+=lib/libsys
lib/libsys:
	make -C $(ROTDIR)/$@

PHONY+=lib/libheap
lib/libheap: lib/libc lib/libsys
	make -C $(ROTDIR)/$@

PHONY+=dev/zero
dev/zero: lib/libc lib/libsys lib/libheap
	make -C $(ROTDIR)/$@

PHONY+=dev/rand
dev/rand: lib/libc lib/libsys lib/libheap
	make -C $(ROTDIR)/$@

PHONY+=dev/fd0
dev/fd0: lib/libc lib/libsys lib/libheap
	make -C $(ROTDIR)/$@

PHONY+=dev/ata
dev/ata: lib/libc lib/libsys lib/libheap
	make -C $(ROTDIR)/$@

PHONY+=usr/wtest
usr/wtest: lib/libc lib/libsys lib/libheap
	make -C $(ROTDIR)/$@

PHONY+=usr/mtest
usr/mtest: lib/libc lib/libsys lib/libheap
	make -C $(ROTDIR)/$@

.PHONY: $(PHONY)
