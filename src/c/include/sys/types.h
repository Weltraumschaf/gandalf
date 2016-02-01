#pragma once

#include <stdint.h> /* for uint32_t */
#include <sys/cdefs.h>

__BEGIN_DECLS

typedef int ssize_t;
/* Used for some file attributes. */
typedef uint32_t mode_t;
typedef uint32_t pid_t;
typedef long int off_t;

__END_DECLS
