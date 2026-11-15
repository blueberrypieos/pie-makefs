/*
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright (c) 2026 The Blueberry Pie OS Authors
 */
#include "nbtool_config.h"
#include <err.h>
#include "makefs.h"

#define	NOT_BUILT(fs)							\
void fs ## _prep_opts(fsinfo_t *f) { (void)f; errx(1, #fs " is not built, only zfs"); } \
int fs ## _parse_opts(const char *o, fsinfo_t *f) { (void)o; (void)f; return (0); } \
void fs ## _cleanup_opts(fsinfo_t *f) { (void)f; } \
void fs ## _makefs(const char *i, const char *d, fsnode *r, fsinfo_t *f) \
{ (void)i; (void)d; (void)r; (void)f; errx(1, #fs " is not built, only zfs"); }

NOT_BUILT(cd9660)
NOT_BUILT(ffs)
NOT_BUILT(msdos)
