<!-- SPDX-License-Identifier: BSD-2-Clause -->
<!-- Copyright (c) 2026 The Blueberry Pie OS Authors -->
# pie-makefs

FreeBSD's makefs, with only its zfs writer, built for Linux with libbsd.
It writes a ZFS pool image from a directory tree, without the ZFS kernel
module. The same tree, options and `-T` time give the same image.

`src/freebsd-src` is a submodule at FreeBSD's release tag. Initialise it
with `git submodule update --init --depth 1`. `make` builds
`build/pie-makefs`, and `make install DESTDIR=DIR` installs
`/usr/bin/pie-makefs` and its manual page.

Build a source package with `pie-source source`, extract it with
`dpkg-source -x`, then run `dpkg-buildpackage -b -us -uc` in the extracted
tree.

Example:

    LC_ALL=C pie-makefs -t zfs -T "$SOURCE_DATE_EPOCH" -s 1024m \
        -o poolname=pie -o rootpath=/ -o bootfs=pie/sys/default \
        -o 'fs=pie;canmount=off;mountpoint=none' \
        -o 'fs=pie/sys;canmount=off;mountpoint=none' \
        -o 'fs=pie/sys/default;mountpoint=/' pool.zfs ROOT
