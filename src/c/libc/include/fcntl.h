#ifndef __FCNTL_H_
#define __FCNTL_H_

/*
 * From lib/libc//musl-0.9.15/include/fcntl.h
 *
 * See https://www.gnu.org/software/libc/manual/html_node/Opening-and-Closing-Files.html
 */

#include <sys/cdefs.h>

__BEGIN_DECLS

int open(const char *, int, ...);

__END_DECLS

#endif
