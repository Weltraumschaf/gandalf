#ifndef __FCNTL_H_
#define __FCNTL_H_

/*
 * From lib/libc//musl-0.9.15/include/fcntl.h
 *
 * See https://www.gnu.org/software/libc/manual/html_node/Opening-and-Closing-Files.html
 */

#include <sys/cdefs.h>

__BEGIN_DECLS

int open(const char * path, int oflags);
int open(const char * path, int oflags, mode_t mode);

__END_DECLS

#endif
