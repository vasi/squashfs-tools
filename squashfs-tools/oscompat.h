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

#endif
