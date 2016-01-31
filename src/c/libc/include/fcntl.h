#pragma once

/*
 * From lib/libc//musl-0.9.15/include/fcntl.h
 *
 * See https://www.gnu.org/software/libc/manual/html_node/Opening-and-Closing-Files.html
 */

#include <sys/cdefs.h>

__BEGIN_DECLS

/* open/fcntl - O_SYNC is only implemented on blocks devices and on files
   located on an ext2 file system */
/*
 * From dietlibc include/fnctl.h
 */
//#define O_ACCMODE	   0003
//#define O_RDONLY	     00
//#define O_WRONLY	     01
#define O_RDWR		     02
//#define O_CREAT		   0100	/* not fcntl */
//#define O_EXCL		   0200	/* not fcntl */
//#define O_NOCTTY	   0400	/* not fcntl */
//#define O_TRUNC		  01000	/* not fcntl */
//#define O_APPEND	  02000
//#define O_NONBLOCK	  04000
//#define O_NDELAY	O_NONBLOCK
//#define O_SYNC		 010000
//#define FASYNC		 020000	/* fcntl, for BSD compatibility */
//#define O_DIRECT	 040000	/* direct disk access hint - currently ignored */
//#define O_LARGEFILE	0100000
//#define O_DIRECTORY	0200000	/* must be a directory */
//#define O_NOFOLLOW	0400000 /* don't follow links */
//#define O_NOATIME	01000000

int open(const char * path, int oflags, ...);
//int open(const char * path, int oflags, mode_t mode);

__END_DECLS
