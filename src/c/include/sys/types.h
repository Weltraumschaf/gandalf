#pragma once

#include <stdint.h> /* for uint32_t */
#include <sys/cdefs.h>

__BEGIN_DECLS

typedef int ssize_t;
typedef int fpos_t;

/* Used for some file attributes. */
typedef uint32_t pid_t;
typedef long int off_t;
typedef uint32_t dev_t;
typedef uint16_t gid_t;
typedef uint16_t mode_t;
typedef uint16_t nlink_t;
typedef uint16_t uid_t;

__END_DECLS
