#ifndef OSCOMPAT_H
#define OSCOMPAT_H

/*
 * Compatibility with non-Linux OSes
 *
 * Copyright (c) 2012 Dave Vasilevsky <dave@vasilevsky.ca>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * oscompat.h
 */

#include <fnmatch.h>
#ifndef FNM_EXTMATCH // glibc extension
	#define FNM_EXTMATCH 0
#endif

#ifdef XATTR_SUPPORT
	#include <sys/xattr.h>
	#ifdef XATTR_NOFOLLOW // Apple's weird xattrs
		#define llistxattr(path_, buf_, sz_) \
			listxattr(path_, buf_, sz_, XATTR_NOFOLLOW)
		#define lgetxattr(path_, name_, val_, sz_) \
			getxattr(path_, name_, val_, sz_, 0, XATTR_NOFOLLOW)
		#define lsetxattr(path_, name_, val_, sz_, flags_) \
			setxattr(path_, name_, val_, sz_, 0, flags_ | XATTR_NOFOLLOW)
	#endif
#endif

#ifdef linux
	#include <endian.h>
#elif defined(__HAIKU__)
	#include <posix/endian.h>
#elif defined(__sun__)
	#define __BIG_ENDIAN 4321
	#define __LITTLE_ENDIAN 1234
	#include <sys/isa_defs.h>
	#ifdef _LITTLE_ENDIAN
		#define __BYTE_ORDER __LITTLE_ENDIAN
	#else
		#define __BYTE_ORDER __BIG_ENDIAN
	#endif
#else
	#define __BYTE_ORDER BYTE_ORDER
	#define __BIG_ENDIAN BIG_ENDIAN
	#define __LITTLE_ENDIAN LITTLE_ENDIAN
	#ifdef __APPLE__
		#include <machine/byte_order.h>
	#elif defined(__QNX__)
		#include <sys/param.h>
	#else
		#include <sys/types.h>
		#include <machine/endian.h>
	#endif
#endif

#if defined(linux) || defined(__sun__)
	#define USE_SYSCONF 1
	#include <sys/sysinfo.h>
#elif !defined(__QNX__) && !defined(__minix) && !defined(__HAIKU__)
	#define USE_SYSCTL 1
	#include <sys/param.h>
	#include <sys/sysctl.h>
#endif

#ifdef __sun__
	#include <sys/mkdev.h>
#endif
#ifdef __QNX__
	#include <sys/sysmacros.h>
	#include <sys/netmgr.h>
	#define xmakedev(_a,_b) makedev(ND_LOCAL_NODE,(_a),(_b))
#elif defined(__HAIKU__)
	#define xmakedev(_a, _b) (0) // Haiku has no dev #s
	#define major(_x) (0)
	#define minor(_x) (0)
#else
	#define xmakedev(_a,_b) makedev((_a),(_b))
#endif

#if !defined(__QNX__) && !defined(__HAIKU__)
	#include <sys/termios.h>
#endif

#ifdef __QNX__
	#include <nbutil.h> // For asprintf
#endif

#ifdef __minix
	#include <sys/stat.h>
	#include <unistd.h>
	static inline int lchown(const char *path, uid_t o, gid_t g) {
		struct stat st;
		int err = lstat(path, &st);
		if (!err && !S_ISLNK(st.st_mode))
			err = chown(path, o, g);
		return err;
	}
#endif

#endif
