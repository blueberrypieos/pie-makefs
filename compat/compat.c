/*
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright (c) 2026 The Blueberry Pie OS Authors
 */
#include "nbtool_config.h"
#include <err.h>
#include <errno.h>
#include <stdlib.h>

int
pwcache_userdb(int (*a)(int), void (*b)(void), struct passwd *(*c)(const char *),
    struct passwd *(*d)(uid_t))
{
	(void)a; (void)b; (void)c; (void)d;
	warnx("-N is not supported");
	errno = ENOTSUP;
	return (-1);
}

int
pwcache_groupdb(int (*a)(int), void (*b)(void), struct group *(*c)(const char *),
    struct group *(*d)(gid_t))
{
	(void)a; (void)b; (void)c; (void)d;
	warnx("-N is not supported");
	errno = ENOTSUP;
	return (-1);
}

static int
no_flags(char **s, unsigned long *set, unsigned long *clr)
{
	*set = 0;
	if (clr != NULL)
		*clr = 0;
	if (**s == '\0' || strcmp(*s, "none") == 0)
		return (0);
	errno = EINVAL;
	return (1);
}

int
strtofflags(char **s, unsigned long *set, unsigned long *clr)
{
	return (no_flags(s, set, clr));
}

int
string_to_flags(char **s, unsigned long *set, unsigned long *clr)
{
	return (no_flags(s, set, clr));
}

char *
flags_to_string(unsigned long f, const char *def)
{
	(void)f;
	return (strdup(def != NULL ? def : "none"));
}

int
uid_from_user(const char *name, uid_t *uid)
{
	(void)uid;
	warnx("user `%s': names need -N, which is not supported", name);
	return (-1);
}

int
gid_from_group(const char *name, gid_t *gid)
{
	(void)gid;
	warnx("group `%s': names need -N, which is not supported", name);
	return (-1);
}

int
setpassent(int x)
{
	(void)x;
	return (1);
}

int
setgroupent(int x)
{
	(void)x;
	return (1);
}
