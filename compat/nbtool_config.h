/*
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright (c) 2026 The Blueberry Pie OS Authors
 */
#ifndef PIE_NBTOOL_CONFIG_H
#define PIE_NBTOOL_CONFIG_H
#define HAVE_STRUCT_STAT_ST_FLAGS 0
#define HAVE_STRUCT_STAT_ST_MTIMENSEC 1
#define st_atimensec st_atim.tv_nsec
#define st_mtimensec st_mtim.tv_nsec
#define st_ctimensec st_ctim.tv_nsec
#include <sys/types.h>
#include <sys/param.h>
#include <sys/time.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#ifndef __unused
#define __unused __attribute__((__unused__))
#endif
#ifndef __va_list
#define __va_list va_list
#endif
#ifndef nitems
#define nitems(x) (sizeof((x)) / sizeof((x)[0]))
#endif
#ifndef roundup2
#define roundup2(x, y) (((x) + ((y) - 1)) & (~((__typeof(x))(y) - 1)))
#endif
#ifndef rounddown2
#define rounddown2(x, y) ((x) & (~((__typeof(x))(y) - 1)))
#endif
#define __bitcountl(x) __builtin_popcountl(x)
static inline int flsll(long long x) { return x == 0 ? 0 : 64 - __builtin_clzll((unsigned long long)x); }
static inline int flsl(long x) { return x == 0 ? 0 : 64 - __builtin_clzl((unsigned long)x); }
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>
#ifndef UID_MAX
#define UID_MAX UINT32_MAX
#endif
#ifndef GID_MAX
#define GID_MAX UINT32_MAX
#endif
int pwcache_userdb(int (*)(int), void (*)(void), struct passwd *(*)(const char *), struct passwd *(*)(uid_t));
int pwcache_groupdb(int (*)(int), void (*)(void), struct group *(*)(const char *), struct group *(*)(gid_t));
#ifndef __predict_false
#define __predict_false(x) __builtin_expect(!!(x), 0)
#endif
int strtofflags(char **, unsigned long *, unsigned long *);
int setpassent(int);
int setgroupent(int);
#endif
