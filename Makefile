# SPDX-License-Identifier: BSD-2-Clause
# Copyright (c) 2026 The Blueberry Pie OS Authors
#
# make [SRC=DIR] [O=DIR]
# make install DESTDIR=DIR
#
# Builds pie-makefs, FreeBSD's makefs with only its zfs writer, for Linux
# with libbsd. SRC is the freebsd-src tree, src/freebsd-src by default, and
# O the build directory. patches/ applies to a copy of the files it changes.
# CFLAGS, CPPFLAGS and LDFLAGS are added.

SRC ?= src/freebsd-src
O ?= build
CC ?= cc
M = $(SRC)/usr.sbin/makefs
PATCHED = $(O)/patched
PATCHES = $(sort $(wildcard patches/*.patch))
PFILES = usr.sbin/makefs/walk.c usr.sbin/makefs/zfs.c usr.sbin/makefs/zfs/fs.c usr.sbin/makefs/zfs/objset.c

SRCS = \
	$(M)/makefs.c $(PATCHED)/usr.sbin/makefs/walk.c $(M)/mtree.c $(PATCHED)/usr.sbin/makefs/zfs.c \
	$(M)/zfs/dsl.c $(PATCHED)/usr.sbin/makefs/zfs/fs.c $(PATCHED)/usr.sbin/makefs/zfs/objset.c \
	$(M)/zfs/vdev.c $(M)/zfs/zap.c \
	$(SRC)/stand/libsa/zfs/nvlist.c \
	$(SRC)/contrib/mtree/getid.c $(SRC)/contrib/mtree/misc.c $(SRC)/contrib/mtree/spec.c \
	$(SRC)/contrib/mknod/pack_dev.c \
	$(SRC)/lib/libnetbsd/efun.c $(SRC)/lib/libnetbsd/strsuftoll.c \
	$(SRC)/sys/kern/subr_sbuf.c \
	compat/compat.c compat/fstypes.c

SYSHDRS = bitstring.h sbuf.h

PIE_CPPFLAGS = -D_GNU_SOURCE -DHAVE_ZFS -DHAVE_NBTOOL_CONFIG_H=1 -DDEFAULT_FSTYPE='"zfs"' \
	-include compat/nbtool_config.h \
	-isystem /usr/include/$(shell $(CC) -dumpmachine)/bsd -isystem /usr/include/bsd \
	-DLIBBSD_OVERLAY -DLIBBSD_NETBSD_VIS \
	-Icompat -I$(O)/include -I$(M) -I$(M)/zfs -I$(SRC)/stand/libsa -I$(SRC)/sys/cddl/boot \
	-I$(SRC)/contrib/mtree -I$(SRC)/contrib/mknod -I$(SRC)/lib/libnetbsd

objname = $(O)/obj/$(subst /,_,$(patsubst $(PATCHED)/%,%,$(patsubst $(SRC)/%,%,$(1:.c=.o))))
OBJS = $(foreach s,$(SRCS),$(call objname,$(s)))
HDRS = $(addprefix $(O)/include/sys/,$(SYSHDRS))

all: $(O)/pie-makefs

$(O)/pie-makefs: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) -lbsd

$(PATCHED)/stamp: $(PATCHES) $(addprefix $(SRC)/,$(PFILES))
	rm -rf $(PATCHED)
	set -e; for f in $(PFILES); do mkdir -p $(PATCHED)/$$(dirname $$f); cp $(SRC)/$$f $(PATCHED)/$$f; done
	set -e; for p in $(PATCHES); do patch -s -p3 -d $(PATCHED) < $$p; done
	touch $@

$(addprefix $(PATCHED)/,$(PFILES)): $(PATCHED)/stamp ;

$(O)/include/sys/%.h: $(SRC)/sys/sys/%.h
	@mkdir -p $(dir $@)
	cp $< $@

define rule
$(call objname,$(1)): $(1) $(HDRS) compat/nbtool_config.h
	@mkdir -p $(O)/obj
	$$(CC) $(PIE_CPPFLAGS) $$(CPPFLAGS) $$(CFLAGS) -c $$< -o $$@
endef
$(foreach s,$(SRCS),$(eval $(call rule,$(s))))

install: $(O)/pie-makefs
	install -D -m 755 $(O)/pie-makefs $(DESTDIR)/usr/bin/pie-makefs
	install -D -m 644 man/pie-makefs.8 $(DESTDIR)/usr/share/man/man8/pie-makefs.8

clean:
	rm -rf $(O)

.PHONY: all install clean
