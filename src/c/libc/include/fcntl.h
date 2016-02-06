#pragma once

/*
 * From lib/libc//musl-0.9.15/include/fcntl.h
 *
 * See
 * https://www.gnu.org/software/libc/manual/html_node/Opening-and-Closing-Files.html
 */

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

// Available Values for oflag:

/**
 * Open the file so that it is read only.
 */
#define O_RDONLY 0
/**
 * Open the file so that it is write only.
 */
#define O_WRONLY 0
/**
 * Open the file so that it can be read from and written to.
 */
#define O_RDWR 0
/**
 * Append new information to the end of the file.
 */
#define O_APPEND 0
/**
 * Initially clear all data from the file.
 */
#define O_TRUNC 0
/**
 * If the file does not exist, create it. If the O_CREAT option is used, then
 * you must include the third parameter.
 */
#define O_CREAT 0
/**
 * Combined with the O_CREAT option, it ensures that the caller must create the
 * file. If the file already exists, the call will fail.
 */
#define O_EXCL 0

// Available Values for mode:

/**
 * Set read rights for the owner to true.
 */
#define S_IRUSR 0
/**
 * Set write rights for the owner to true.
 */
#define S_IWUSR 0
/**
 * Set execution rights for the owner to true.
 */
#define S_IXUSR 0
/**
 * Set read rights for the group to true.
 */
#define S_IRGRP 0
/**
 * Set write rights for the group to true.
 */
#define S_IWGRP 0
/**
 * Set execution rights for the group to true.
 */
#define S_IXGRP 0
/**
 * Set read rights for other users to true.
 */
#define S_IROTH 0
/**
 * Set write rights for other users to true.
 */
#define S_IWOTH 0
/**
 * Set execution rights for other users to true.
 */
#define S_IXOTH 0

int open(const char *path, int oflags, mode_t mode);

__END_DECLS
