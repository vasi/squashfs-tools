#ifndef SQUASHFS_FS
#define SQUASHFS_FS
/*
 * Squashfs
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@lougher.demon.co.uk>
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
 * squashfs_fs.h
 */

#if 0
#ifndef CONFIG_SQUASHFS_2_0_COMPATIBILITY
#define CONFIG_SQUASHFS_2_0_COMPATIBILITY
#endif
#endif

#define SQUASHFS_CACHED_FRAGMENTS	CONFIG_SQUASHFS_FRAGMENT_CACHE_SIZE	
#define SQUASHFS_MAJOR			4
#define SQUASHFS_MINOR			0
#define SQUASHFS_MAGIC			0x73717368
#define SQUASHFS_MAGIC_SWAP		0x68737173
#define SQUASHFS_START			0

/* size of metadata (inode and directory) blocks */
#define SQUASHFS_METADATA_SIZE		8192
#define SQUASHFS_METADATA_LOG		13

/* default size of data blocks */
#define SQUASHFS_FILE_SIZE		131072
#define SQUASHFS_FILE_LOG		17

#define SQUASHFS_FILE_MAX_SIZE		1048576

/* Max number of uids and gids */
#define SQUASHFS_IDS			65536

/* Max length of filename (not 255) */
#define SQUASHFS_NAME_LEN		256

#define SQUASHFS_INVALID		((long long) 0xffffffffffff)
#define SQUASHFS_INVALID_FRAG		((unsigned int) 0xffffffff)
#define SQUASHFS_INVALID_BLK		((long long) -1)
#define SQUASHFS_USED_BLK		((long long) -2)

/* Filesystem flags */
#define SQUASHFS_NOI			0
#define SQUASHFS_NOD			1
#define SQUASHFS_CHECK			2
#define SQUASHFS_NOF			3
#define SQUASHFS_NO_FRAG		4
#define SQUASHFS_ALWAYS_FRAG		5
#define SQUASHFS_DUPLICATE		6
#define SQUASHFS_EXPORT			7

#define SQUASHFS_BIT(flag, bit)		((flag >> bit) & 1)

#define SQUASHFS_UNCOMPRESSED_INODES(flags)	SQUASHFS_BIT(flags, \
						SQUASHFS_NOI)

#define SQUASHFS_UNCOMPRESSED_DATA(flags)	SQUASHFS_BIT(flags, \
						SQUASHFS_NOD)

#define SQUASHFS_UNCOMPRESSED_FRAGMENTS(flags)	SQUASHFS_BIT(flags, \
						SQUASHFS_NOF)

#define SQUASHFS_NO_FRAGMENTS(flags)		SQUASHFS_BIT(flags, \
						SQUASHFS_NO_FRAG)

#define SQUASHFS_ALWAYS_FRAGMENTS(flags)	SQUASHFS_BIT(flags, \
						SQUASHFS_ALWAYS_FRAG)

#define SQUASHFS_DUPLICATES(flags)		SQUASHFS_BIT(flags, \
						SQUASHFS_DUPLICATE)

#define SQUASHFS_EXPORTABLE(flags)		SQUASHFS_BIT(flags, \
						SQUASHFS_EXPORT)

#define SQUASHFS_CHECK_DATA(flags)		SQUASHFS_BIT(flags, \
						SQUASHFS_CHECK)

#define SQUASHFS_MKFLAGS(noi, nod, check_data, nof, no_frag, always_frag, \
		duplicate_checking, exportable)	(noi | (nod << 1) | (check_data << 2) \
		| (nof << 3) | (no_frag << 4) | (always_frag << 5) | \
		(duplicate_checking << 6) | (exportable << 7))

/* Max number of types and file types */
#define SQUASHFS_DIR_TYPE		1
#define SQUASHFS_FILE_TYPE		2
#define SQUASHFS_SYMLINK_TYPE		3
#define SQUASHFS_BLKDEV_TYPE		4
#define SQUASHFS_CHRDEV_TYPE		5
#define SQUASHFS_FIFO_TYPE		6
#define SQUASHFS_SOCKET_TYPE		7
#define SQUASHFS_LDIR_TYPE		8
#define SQUASHFS_LREG_TYPE		9

/* 1.0 filesystem type definitions */
#define SQUASHFS_TYPES			5
#define SQUASHFS_IPC_TYPE		0

/* Flag whether block is compressed or uncompressed, bit is set if block is
 * uncompressed */
#define SQUASHFS_COMPRESSED_BIT		(1 << 15)

#define SQUASHFS_COMPRESSED_SIZE(B)	(((B) & ~SQUASHFS_COMPRESSED_BIT) ? \
		(B) & ~SQUASHFS_COMPRESSED_BIT :  SQUASHFS_COMPRESSED_BIT)

#define SQUASHFS_COMPRESSED(B)		(!((B) & SQUASHFS_COMPRESSED_BIT))

#define SQUASHFS_COMPRESSED_BIT_BLOCK		(1 << 24)

#define SQUASHFS_COMPRESSED_SIZE_BLOCK(B)	((B) & \
	~SQUASHFS_COMPRESSED_BIT_BLOCK)

#define SQUASHFS_COMPRESSED_BLOCK(B)	(!((B) & SQUASHFS_COMPRESSED_BIT_BLOCK))

/*
 * Inode number ops.  Inodes consist of a compressed block number, and an
 * uncompressed  offset within that block
 */
#define SQUASHFS_INODE_BLK(a)		((unsigned int) ((a) >> 16))

#define SQUASHFS_INODE_OFFSET(a)	((unsigned int) ((a) & 0xffff))

#define SQUASHFS_MKINODE(A, B)		((squashfs_inode_t)(((squashfs_inode_t) (A)\
					<< 16) + (B)))

/* Compute 32 bit VFS inode number from squashfs inode number */
#define SQUASHFS_MK_VFS_INODE(a, b)	((unsigned int) (((a) << 8) + \
					((b) >> 2) + 1))
/* XXX */

/* Translate between VFS mode and squashfs mode */
#define SQUASHFS_MODE(a)		((a) & 0xfff)

/* fragment and fragment table defines */
#define SQUASHFS_FRAGMENT_BYTES(A)	((A) * sizeof(struct squashfs_fragment_entry))

#define SQUASHFS_FRAGMENT_INDEX(A)	(SQUASHFS_FRAGMENT_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FRAGMENT_INDEX_OFFSET(A)	(SQUASHFS_FRAGMENT_BYTES(A) % \
						SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FRAGMENT_INDEXES(A)	((SQUASHFS_FRAGMENT_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FRAGMENT_INDEX_BYTES(A)	(SQUASHFS_FRAGMENT_INDEXES(A) *\
						sizeof(long long))

/* inode lookup table defines */
#define SQUASHFS_LOOKUP_BYTES(A)	((A) * sizeof(squashfs_inode_t))

#define SQUASHFS_LOOKUP_BLOCK(A)		(SQUASHFS_LOOKUP_BYTES(A) / \
						SQUASHFS_METADATA_SIZE)

#define SQUASHFS_LOOKUP_BLOCK_OFFSET(A)		(SQUASHFS_LOOKUP_BYTES(A) % \
						SQUASHFS_METADATA_SIZE)

#define SQUASHFS_LOOKUP_BLOCKS(A)	((SQUASHFS_LOOKUP_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_LOOKUP_BLOCK_BYTES(A)	(SQUASHFS_LOOKUP_BLOCKS(A) *\
					sizeof(long long))

/* uid lookup table defines */
#define SQUASHFS_ID_BYTES(A)	((A) * sizeof(unsigned int))

#define SQUASHFS_ID_BLOCK(A)		(SQUASHFS_ID_BYTES(A) / \
						SQUASHFS_METADATA_SIZE)

#define SQUASHFS_ID_BLOCK_OFFSET(A)		(SQUASHFS_ID_BYTES(A) % \
						SQUASHFS_METADATA_SIZE)

#define SQUASHFS_ID_BLOCKS(A)	((SQUASHFS_ID_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_ID_BLOCK_BYTES(A)	(SQUASHFS_ID_BLOCKS(A) *\
					sizeof(long long))

/* cached data constants for filesystem */
#define SQUASHFS_CACHED_BLKS		8

#define SQUASHFS_MAX_FILE_SIZE_LOG	64

#define SQUASHFS_MAX_FILE_SIZE		((long long) 1 << \
					(SQUASHFS_MAX_FILE_SIZE_LOG - 2))

#define SQUASHFS_MARKER_BYTE		0xff

/* meta index cache */
#define SQUASHFS_META_INDEXES	(SQUASHFS_METADATA_SIZE / sizeof(unsigned int))
#define SQUASHFS_META_ENTRIES	31
#define SQUASHFS_META_NUMBER	8
#define SQUASHFS_SLOTS		4

struct meta_entry {
	long long		data_block;
	unsigned int		index_block;
	unsigned short		offset;
	unsigned short		pad;
};

struct meta_index {
	unsigned int		inode_number;
	unsigned int		offset;
	unsigned short		entries;
	unsigned short		skip;
	unsigned short		locked;
	unsigned short		pad;
	struct meta_entry	meta_entry[SQUASHFS_META_ENTRIES];
};


/*
 * definitions for structures on disk
 */

typedef long long		squashfs_block_t;
typedef long long		squashfs_inode_t;

#define COMPRESSION_ZLIB 1

struct squashfs_super_block {
	__le32			s_magic;
	__le32			inodes;
	__le32			mkfs_time /* time of filesystem creation */;
	__le32			block_size;
	__le32			fragments;
	__le16			compression;
	__le16			block_log;
	__le16			flags;
	__le16			no_ids;
	__le16			s_major;
	__le16			s_minor;
	__le64			root_inode;
	__le64			bytes_used;
	__le64			id_table_start;
	__le64			xattr_table_start;
	__le64			inode_table_start;
	__le64			directory_table_start;
	__le64			fragment_table_start;
	__le64			lookup_table_start;
};

struct squashfs_dir_index {
	__le32			index;
	__le32			start_block;
	__le32			size;
	unsigned char		name[0];
};

#define SQUASHFS_BASE_INODE_HEADER		\
	__le16			inode_type;	\
	__le16			mode;	\
	__le16			uid;		\
	__le16			guid;		\
	__le32			mtime;		\
	__le32	 		inode_number;

struct squashfs_base_inode_header {
	SQUASHFS_BASE_INODE_HEADER;
};

struct squashfs_ipc_inode_header {
	SQUASHFS_BASE_INODE_HEADER;
	__le32			nlink;
};

struct squashfs_dev_inode_header {
	SQUASHFS_BASE_INODE_HEADER;
	__le32			nlink;
	__le32			rdev;
};
	
struct squashfs_symlink_inode_header {
	SQUASHFS_BASE_INODE_HEADER;
	__le32			nlink;
	__le32			symlink_size;
	char			symlink[0];
};

struct squashfs_reg_inode_header {
	SQUASHFS_BASE_INODE_HEADER;
	__le32			start_block;
	__le32			fragment;
	__le32			offset;
	__le32			file_size;
	__le16			block_list[0];
};

struct squashfs_lreg_inode_header {
	SQUASHFS_BASE_INODE_HEADER;
	__le64			start_block;
	__le64			file_size;
	__le64			sparse;
	__le32			nlink;
	__le32			fragment;
	__le32			offset;
	__le32			xattr;
	__le16			block_list[0];
};

struct squashfs_dir_inode_header {
	SQUASHFS_BASE_INODE_HEADER;
	__le32			start_block;
	__le32			nlink;
	__le16			file_size;
	__le16			offset;
	__le32			parent_inode;
};

struct squashfs_ldir_inode_header {
	SQUASHFS_BASE_INODE_HEADER;
	__le32			nlink;
	__le32			file_size;
	__le32			start_block;
	__le32			parent_inode;
	__le16			i_count;
	__le16			offset;
	struct squashfs_dir_index	index[0];
};

union squashfs_inode_header {
	struct squashfs_base_inode_header	base;
	struct squashfs_dev_inode_header	dev;
	struct squashfs_symlink_inode_header	symlink;
	struct squashfs_reg_inode_header	reg;
	struct squashfs_lreg_inode_header	lreg;
	struct squashfs_dir_inode_header	dir;
	struct squashfs_ldir_inode_header	ldir;
	struct squashfs_ipc_inode_header	ipc;
};
	
struct squashfs_dir_entry {
	__le16			offset;
	__le16			inode_number;
	__le16			type;
	__le16			size;
	char			name[0];
};

struct squashfs_dir_header {
	__le32			count;
	__le32			start_block;
	__le32			inode_number;
};

struct squashfs_fragment_entry {
	__le64			start_block;
	__le32			size;
	unsigned int		unused;
};

extern int squashfs_uncompress_block(void *d, int dstlen, void *s, int srclen);
extern int squashfs_uncompress_init(void);
extern int squashfs_uncompress_exit(void);

/*
 * macros to convert each packed bitfield structure from little endian to big
 * endian and vice versa.  These are needed when creating or using a filesystem
 * on a machine with different byte ordering to the target architecture.
 *
 */

#define SQUASHFS_SWAP_START \
	int bits;\
	int b_pos;\
	unsigned long long val;\
	unsigned char *s;\
	unsigned char *d;

#define SQUASHFS_SWAP_SUPER_BLOCK(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_super_block));\
	SQUASHFS_SWAP((s)->s_magic, d, 0, 32);\
	SQUASHFS_SWAP((s)->inodes, d, 32, 32);\
	SQUASHFS_SWAP((s)->bytes_used_2, d, 64, 32);\
	SQUASHFS_SWAP((s)->uid_start_2, d, 96, 32);\
	SQUASHFS_SWAP((s)->guid_start_2, d, 128, 32);\
	SQUASHFS_SWAP((s)->inode_table_start_2, d, 160, 32);\
	SQUASHFS_SWAP((s)->directory_table_start_2, d, 192, 32);\
	SQUASHFS_SWAP((s)->s_major, d, 224, 16);\
	SQUASHFS_SWAP((s)->s_minor, d, 240, 16);\
	SQUASHFS_SWAP((s)->block_size_1, d, 256, 16);\
	SQUASHFS_SWAP((s)->block_log, d, 272, 16);\
	SQUASHFS_SWAP((s)->flags, d, 288, 8);\
	SQUASHFS_SWAP((s)->no_uids, d, 296, 8);\
	SQUASHFS_SWAP((s)->no_guids, d, 304, 8);\
	SQUASHFS_SWAP((s)->mkfs_time, d, 312, 32);\
	SQUASHFS_SWAP((s)->root_inode, d, 344, 64);\
	SQUASHFS_SWAP((s)->block_size, d, 408, 32);\
	SQUASHFS_SWAP((s)->fragments, d, 440, 32);\
	SQUASHFS_SWAP((s)->fragment_table_start_2, d, 472, 32);\
	SQUASHFS_SWAP((s)->bytes_used, d, 504, 64);\
	SQUASHFS_SWAP((s)->uid_start, d, 568, 64);\
	SQUASHFS_SWAP((s)->guid_start, d, 632, 64);\
	SQUASHFS_SWAP((s)->inode_table_start, d, 696, 64);\
	SQUASHFS_SWAP((s)->directory_table_start, d, 760, 64);\
	SQUASHFS_SWAP((s)->fragment_table_start, d, 824, 64);\
	SQUASHFS_SWAP((s)->lookup_table_start, d, 888, 64);\
}

#define SQUASHFS_SWAP_BASE_INODE_CORE(s, d, n)\
	SQUASHFS_MEMSET(s, d, n);\
	SQUASHFS_SWAP((s)->inode_type, d, 0, 4);\
	SQUASHFS_SWAP((s)->mode, d, 4, 12);\
	SQUASHFS_SWAP((s)->uid, d, 16, 8);\
	SQUASHFS_SWAP((s)->guid, d, 24, 8);\
	SQUASHFS_SWAP((s)->mtime, d, 32, 32);\
	SQUASHFS_SWAP((s)->inode_number, d, 64, 32);

#define SQUASHFS_SWAP_BASE_INODE_HEADER(s, d, n) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE(s, d, n)\
}

#define SQUASHFS_SWAP_IPC_INODE_HEADER(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE(s, d, \
			sizeof(struct squashfs_ipc_inode_header))\
	SQUASHFS_SWAP((s)->nlink, d, 96, 32);\
}

#define SQUASHFS_SWAP_DEV_INODE_HEADER(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE(s, d, \
			sizeof(struct squashfs_dev_inode_header)); \
	SQUASHFS_SWAP((s)->nlink, d, 96, 32);\
	SQUASHFS_SWAP((s)->rdev, d, 128, 16);\
}

#define SQUASHFS_SWAP_SYMLINK_INODE_HEADER(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE(s, d, \
			sizeof(struct squashfs_symlink_inode_header));\
	SQUASHFS_SWAP((s)->nlink, d, 96, 32);\
	SQUASHFS_SWAP((s)->symlink_size, d, 128, 16);\
}

#define SQUASHFS_SWAP_REG_INODE_HEADER(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE(s, d, \
			sizeof(struct squashfs_reg_inode_header));\
	SQUASHFS_SWAP((s)->start_block, d, 96, 64);\
	SQUASHFS_SWAP((s)->fragment, d, 160, 32);\
	SQUASHFS_SWAP((s)->offset, d, 192, 32);\
	SQUASHFS_SWAP((s)->file_size, d, 224, 32);\
}

#define SQUASHFS_SWAP_LREG_INODE_HEADER(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE(s, d, \
			sizeof(struct squashfs_lreg_inode_header));\
	SQUASHFS_SWAP((s)->nlink, d, 96, 32);\
	SQUASHFS_SWAP((s)->start_block, d, 128, 64);\
	SQUASHFS_SWAP((s)->fragment, d, 192, 32);\
	SQUASHFS_SWAP((s)->offset, d, 224, 32);\
	SQUASHFS_SWAP((s)->file_size, d, 256, 64);\
}

#define SQUASHFS_SWAP_DIR_INODE_HEADER(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE(s, d, \
			sizeof(struct squashfs_dir_inode_header));\
	SQUASHFS_SWAP((s)->nlink, d, 96, 32);\
	SQUASHFS_SWAP((s)->file_size, d, 128, 19);\
	SQUASHFS_SWAP((s)->offset, d, 147, 13);\
	SQUASHFS_SWAP((s)->start_block, d, 160, 32);\
	SQUASHFS_SWAP((s)->parent_inode, d, 192, 32);\
}

#define SQUASHFS_SWAP_LDIR_INODE_HEADER(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE(s, d, \
			sizeof(struct squashfs_ldir_inode_header));\
	SQUASHFS_SWAP((s)->nlink, d, 96, 32);\
	SQUASHFS_SWAP((s)->file_size, d, 128, 27);\
	SQUASHFS_SWAP((s)->offset, d, 155, 13);\
	SQUASHFS_SWAP((s)->start_block, d, 168, 32);\
	SQUASHFS_SWAP((s)->i_count, d, 200, 16);\
	SQUASHFS_SWAP((s)->parent_inode, d, 216, 32);\
}

#define SQUASHFS_SWAP_DIR_INDEX(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_dir_index));\
	SQUASHFS_SWAP((s)->index, d, 0, 32);\
	SQUASHFS_SWAP((s)->start_block, d, 32, 32);\
	SQUASHFS_SWAP((s)->size, d, 64, 8);\
}

#define SQUASHFS_SWAP_DIR_HEADER(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_dir_header));\
	SQUASHFS_SWAP((s)->count, d, 0, 8);\
	SQUASHFS_SWAP((s)->start_block, d, 8, 32);\
	SQUASHFS_SWAP((s)->inode_number, d, 40, 32);\
}

#define SQUASHFS_SWAP_DIR_ENTRY(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_dir_entry));\
	SQUASHFS_SWAP((s)->offset, d, 0, 13);\
	SQUASHFS_SWAP((s)->type, d, 13, 3);\
	SQUASHFS_SWAP((s)->size, d, 16, 8);\
	SQUASHFS_SWAP((s)->inode_number, d, 24, 16);\
}

#define SQUASHFS_SWAP_FRAGMENT_ENTRY(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_fragment_entry));\
	SQUASHFS_SWAP((s)->start_block, d, 0, 64);\
	SQUASHFS_SWAP((s)->size, d, 64, 32);\
}

#define SQUASHFS_SWAP_INODE_T(s, d) SQUASHFS_SWAP_LONG_LONGS(s, d, 1)

#define SQUASHFS_SWAP_SHORTS(s, d, n) {\
	int entry;\
	int bit_position;\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, n * 2);\
	for(entry = 0, bit_position = 0; entry < n; entry++, bit_position += \
			16)\
		SQUASHFS_SWAP(s[entry], d, bit_position, 16);\
}

#define SQUASHFS_SWAP_INTS(s, d, n) {\
	int entry;\
	int bit_position;\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, n * 4);\
	for(entry = 0, bit_position = 0; entry < n; entry++, bit_position += \
			32)\
		SQUASHFS_SWAP(s[entry], d, bit_position, 32);\
}

#define SQUASHFS_SWAP_LONG_LONGS(s, d, n) {\
	int entry;\
	int bit_position;\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, n * 8);\
	for(entry = 0, bit_position = 0; entry < n; entry++, bit_position += \
			64)\
		SQUASHFS_SWAP(s[entry], d, bit_position, 64);\
}

#define SQUASHFS_SWAP_DATA(s, d, n, bits) {\
	int entry;\
	int bit_position;\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, n * bits / 8);\
	for(entry = 0, bit_position = 0; entry < n; entry++, bit_position += \
			bits)\
		SQUASHFS_SWAP(s[entry], d, bit_position, bits);\
}

#define SQUASHFS_SWAP_FRAGMENT_INDEXES(s, d, n) SQUASHFS_SWAP_LONG_LONGS(s, d, n)
#define SQUASHFS_SWAP_LOOKUP_BLOCKS(s, d, n) SQUASHFS_SWAP_LONG_LONGS(s, d, n)
#define SQUASHFS_SWAP_ID_BLOCKS(s, d, n) SQUASHFS_SWAP_LONG_LONGS(s, d, n)

#ifdef CONFIG_SQUASHFS_1_0_COMPATIBILITY

struct squashfs_base_inode_header_1 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:4; /* index into uid table */
	unsigned int		guid:4; /* index into guid table */
} __attribute__ ((packed));

struct squashfs_ipc_inode_header_1 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:4; /* index into uid table */
	unsigned int		guid:4; /* index into guid table */
	unsigned int		type:4;
	unsigned int		offset:4;
} __attribute__ ((packed));

struct squashfs_dev_inode_header_1 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:4; /* index into uid table */
	unsigned int		guid:4; /* index into guid table */
	unsigned short		rdev;
} __attribute__ ((packed));
	
struct squashfs_symlink_inode_header_1 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:4; /* index into uid table */
	unsigned int		guid:4; /* index into guid table */
	unsigned short		symlink_size;
	char			symlink[0];
} __attribute__ ((packed));

struct squashfs_reg_inode_header_1 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:4; /* index into uid table */
	unsigned int		guid:4; /* index into guid table */
	unsigned int		mtime;
	unsigned int		start_block;
	unsigned int		file_size:32;
	unsigned short		block_list[0];
} __attribute__ ((packed));

struct squashfs_dir_inode_header_1 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:4; /* index into uid table */
	unsigned int		guid:4; /* index into guid table */
	unsigned int		file_size:19;
	unsigned int		offset:13;
	unsigned int		mtime;
	unsigned int		start_block:24;
} __attribute__  ((packed));

union squashfs_inode_header_1 {
	struct squashfs_base_inode_header_1	base;
	struct squashfs_dev_inode_header_1	dev;
	struct squashfs_symlink_inode_header_1	symlink;
	struct squashfs_reg_inode_header_1	reg;
	struct squashfs_dir_inode_header_1	dir;
	struct squashfs_ipc_inode_header_1	ipc;
};

#define SQUASHFS_SWAP_BASE_INODE_CORE_1(s, d, n) \
	SQUASHFS_MEMSET(s, d, n);\
	SQUASHFS_SWAP((s)->inode_type, d, 0, 4);\
	SQUASHFS_SWAP((s)->mode, d, 4, 12);\
	SQUASHFS_SWAP((s)->uid, d, 16, 4);\
	SQUASHFS_SWAP((s)->guid, d, 20, 4);

#define SQUASHFS_SWAP_BASE_INODE_HEADER_1(s, d, n) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_1(s, d, n)\
}

#define SQUASHFS_SWAP_IPC_INODE_HEADER_1(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_1(s, d, \
			sizeof(struct squashfs_ipc_inode_header_1));\
	SQUASHFS_SWAP((s)->type, d, 24, 4);\
	SQUASHFS_SWAP((s)->offset, d, 28, 4);\
}

#define SQUASHFS_SWAP_DEV_INODE_HEADER_1(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_1(s, d, \
			sizeof(struct squashfs_dev_inode_header_1));\
	SQUASHFS_SWAP((s)->rdev, d, 24, 16);\
}

#define SQUASHFS_SWAP_SYMLINK_INODE_HEADER_1(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_1(s, d, \
			sizeof(struct squashfs_symlink_inode_header_1));\
	SQUASHFS_SWAP((s)->symlink_size, d, 24, 16);\
}

#define SQUASHFS_SWAP_REG_INODE_HEADER_1(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_1(s, d, \
			sizeof(struct squashfs_reg_inode_header_1));\
	SQUASHFS_SWAP((s)->mtime, d, 24, 32);\
	SQUASHFS_SWAP((s)->start_block, d, 56, 32);\
	SQUASHFS_SWAP((s)->file_size, d, 88, 32);\
}

#define SQUASHFS_SWAP_DIR_INODE_HEADER_1(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_1(s, d, \
			sizeof(struct squashfs_dir_inode_header_1));\
	SQUASHFS_SWAP((s)->file_size, d, 24, 19);\
	SQUASHFS_SWAP((s)->offset, d, 43, 13);\
	SQUASHFS_SWAP((s)->mtime, d, 56, 32);\
	SQUASHFS_SWAP((s)->start_block, d, 88, 24);\
}

#endif

#ifdef CONFIG_SQUASHFS_2_0_COMPATIBILITY

struct squashfs_dir_index_2 {
	unsigned int		index:27;
	unsigned int		start_block:29;
	unsigned char		size;
	unsigned char		name[0];
} __attribute__ ((packed));

struct squashfs_base_inode_header_2 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:8; /* index into uid table */
	unsigned int		guid:8; /* index into guid table */
} __attribute__ ((packed));

struct squashfs_ipc_inode_header_2 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:8; /* index into uid table */
	unsigned int		guid:8; /* index into guid table */
} __attribute__ ((packed));

struct squashfs_dev_inode_header_2 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:8; /* index into uid table */
	unsigned int		guid:8; /* index into guid table */
	unsigned short		rdev;
} __attribute__ ((packed));
	
struct squashfs_symlink_inode_header_2 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:8; /* index into uid table */
	unsigned int		guid:8; /* index into guid table */
	unsigned short		symlink_size;
	char			symlink[0];
} __attribute__ ((packed));

struct squashfs_reg_inode_header_2 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:8; /* index into uid table */
	unsigned int		guid:8; /* index into guid table */
	unsigned int		mtime;
	unsigned int		start_block;
	unsigned int		fragment;
	unsigned int		offset;
	unsigned int		file_size:32;
	unsigned short		block_list[0];
} __attribute__ ((packed));

struct squashfs_dir_inode_header_2 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:8; /* index into uid table */
	unsigned int		guid:8; /* index into guid table */
	unsigned int		file_size:19;
	unsigned int		offset:13;
	unsigned int		mtime;
	unsigned int		start_block:24;
} __attribute__  ((packed));

struct squashfs_ldir_inode_header_2 {
	unsigned int		inode_type:4;
	unsigned int		mode:12; /* protection */
	unsigned int		uid:8; /* index into uid table */
	unsigned int		guid:8; /* index into guid table */
	unsigned int		file_size:27;
	unsigned int		offset:13;
	unsigned int		mtime;
	unsigned int		start_block:24;
	unsigned int		i_count:16;
	struct squashfs_dir_index_2	index[0];
} __attribute__  ((packed));

union squashfs_inode_header_2 {
	struct squashfs_base_inode_header_2	base;
	struct squashfs_dev_inode_header_2	dev;
	struct squashfs_symlink_inode_header_2	symlink;
	struct squashfs_reg_inode_header_2	reg;
	struct squashfs_dir_inode_header_2	dir;
	struct squashfs_ldir_inode_header_2	ldir;
	struct squashfs_ipc_inode_header_2	ipc;
};
	
struct squashfs_dir_header_2 {
	unsigned int		count:8;
	unsigned int		start_block:24;
} __attribute__ ((packed));

struct squashfs_dir_entry_2 {
	unsigned int		offset:13;
	unsigned int		type:3;
	unsigned int		size:8;
	char			name[0];
} __attribute__ ((packed));

struct squashfs_fragment_entry_2 {
	unsigned int		start_block;
	unsigned int		size;
} __attribute__ ((packed));

#define SQUASHFS_SWAP_BASE_INODE_CORE_2(s, d, n)\
	SQUASHFS_MEMSET(s, d, n);\
	SQUASHFS_SWAP((s)->inode_type, d, 0, 4);\
	SQUASHFS_SWAP((s)->mode, d, 4, 12);\
	SQUASHFS_SWAP((s)->uid, d, 16, 8);\
	SQUASHFS_SWAP((s)->guid, d, 24, 8);\

#define SQUASHFS_SWAP_BASE_INODE_HEADER_2(s, d, n) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_2(s, d, n)\
}

#define SQUASHFS_SWAP_IPC_INODE_HEADER_2(s, d) \
	SQUASHFS_SWAP_BASE_INODE_HEADER_2(s, d, sizeof(struct squashfs_ipc_inode_header_2))

#define SQUASHFS_SWAP_DEV_INODE_HEADER_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_2(s, d, \
			sizeof(struct squashfs_dev_inode_header_2)); \
	SQUASHFS_SWAP((s)->rdev, d, 32, 16);\
}

#define SQUASHFS_SWAP_SYMLINK_INODE_HEADER_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_2(s, d, \
			sizeof(struct squashfs_symlink_inode_header_2));\
	SQUASHFS_SWAP((s)->symlink_size, d, 32, 16);\
}

#define SQUASHFS_SWAP_REG_INODE_HEADER_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_2(s, d, \
			sizeof(struct squashfs_reg_inode_header_2));\
	SQUASHFS_SWAP((s)->mtime, d, 32, 32);\
	SQUASHFS_SWAP((s)->start_block, d, 64, 32);\
	SQUASHFS_SWAP((s)->fragment, d, 96, 32);\
	SQUASHFS_SWAP((s)->offset, d, 128, 32);\
	SQUASHFS_SWAP((s)->file_size, d, 160, 32);\
}

#define SQUASHFS_SWAP_DIR_INODE_HEADER_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_2(s, d, \
			sizeof(struct squashfs_dir_inode_header_2));\
	SQUASHFS_SWAP((s)->file_size, d, 32, 19);\
	SQUASHFS_SWAP((s)->offset, d, 51, 13);\
	SQUASHFS_SWAP((s)->mtime, d, 64, 32);\
	SQUASHFS_SWAP((s)->start_block, d, 96, 24);\
}

#define SQUASHFS_SWAP_LDIR_INODE_HEADER_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_SWAP_BASE_INODE_CORE_2(s, d, \
			sizeof(struct squashfs_ldir_inode_header_2));\
	SQUASHFS_SWAP((s)->file_size, d, 32, 27);\
	SQUASHFS_SWAP((s)->offset, d, 59, 13);\
	SQUASHFS_SWAP((s)->mtime, d, 72, 32);\
	SQUASHFS_SWAP((s)->start_block, d, 104, 24);\
	SQUASHFS_SWAP((s)->i_count, d, 128, 16);\
}

#define SQUASHFS_SWAP_DIR_INDEX_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_dir_index_2));\
	SQUASHFS_SWAP((s)->index, d, 0, 27);\
	SQUASHFS_SWAP((s)->start_block, d, 27, 29);\
	SQUASHFS_SWAP((s)->size, d, 56, 8);\
}
#define SQUASHFS_SWAP_DIR_HEADER_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_dir_header_2));\
	SQUASHFS_SWAP((s)->count, d, 0, 8);\
	SQUASHFS_SWAP((s)->start_block, d, 8, 24);\
}

#define SQUASHFS_SWAP_DIR_ENTRY_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_dir_entry_2));\
	SQUASHFS_SWAP((s)->offset, d, 0, 13);\
	SQUASHFS_SWAP((s)->type, d, 13, 3);\
	SQUASHFS_SWAP((s)->size, d, 16, 8);\
}

#define SQUASHFS_SWAP_FRAGMENT_ENTRY_2(s, d) {\
	SQUASHFS_SWAP_START\
	SQUASHFS_MEMSET(s, d, sizeof(struct squashfs_fragment_entry_2));\
	SQUASHFS_SWAP((s)->start_block, d, 0, 32);\
	SQUASHFS_SWAP((s)->size, d, 32, 32);\
}

#define SQUASHFS_SWAP_FRAGMENT_INDEXES_2(s, d, n) SQUASHFS_SWAP_INTS(s, d, n)

/* fragment and fragment table defines */
#define SQUASHFS_FRAGMENT_BYTES_2(A)	(A * sizeof(struct squashfs_fragment_entry_2))

#define SQUASHFS_FRAGMENT_INDEX_2(A)	(SQUASHFS_FRAGMENT_BYTES_2(A) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FRAGMENT_INDEX_OFFSET_2(A)	(SQUASHFS_FRAGMENT_BYTES_2(A) % \
						SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FRAGMENT_INDEXES_2(A)	((SQUASHFS_FRAGMENT_BYTES_2(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FRAGMENT_INDEX_BYTES_2(A)	(SQUASHFS_FRAGMENT_INDEXES_2(A) *\
						sizeof(int))

#endif

#ifdef __KERNEL__

/*
 * macros used to swap each structure entry, taking into account
 * bitfields and different bitfield placing conventions on differing
 * architectures
 */

#include <asm/byteorder.h>

#ifdef __BIG_ENDIAN
	/* convert from little endian to big endian */
#define SQUASHFS_SWAP(value, p, pos, tbits) _SQUASHFS_SWAP(value, p, pos, \
		tbits, b_pos)
#else
	/* convert from big endian to little endian */ 
#define SQUASHFS_SWAP(value, p, pos, tbits) _SQUASHFS_SWAP(value, p, pos, \
		tbits, 64 - tbits - b_pos)
#endif

#define _SQUASHFS_SWAP(value, p, pos, tbits, SHIFT) {\
	b_pos = pos % 8;\
	val = 0;\
	s = (unsigned char *)p + (pos / 8);\
	d = ((unsigned char *) &val) + 7;\
	for(bits = 0; bits < (tbits + b_pos); bits += 8) \
		*d-- = *s++;\
	value = (val >> (SHIFT))/* & ((1 << tbits) - 1)*/;\
}

#define SQUASHFS_MEMSET(s, d, n)	memset(s, 0, n);

#endif
#endif
