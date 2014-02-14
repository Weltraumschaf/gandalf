/**
 * This source is from https://en.wikipedia.org/wiki/Klibc which is provided
 * under the https://gnu.org/licenses/gpl.html or http://www.linfo.org/bsdlicense.html
 * thanks to the programmers saving me lot of time so i can concetrate on
 * learning to make a kernel.
 */

/*
 * malloc.h
 *
 * Internals for the memory allocator
 */

#include <stdint.h>
#include <stddef.h>
#include "../includes/sysconfig.h"

/*
 * This structure should be a power of two.  This becomes the
 * alignment unit.
 */
struct free_arena_header;

struct arena_header {
    size_t type;
    size_t size;
    struct free_arena_header *next, *prev;
};

#ifdef DEBUG_MALLOC
#define ARENA_TYPE_USED 0x64e69c70
#define ARENA_TYPE_FREE 0x012d610a
#define ARENA_TYPE_HEAD 0x971676b5
#define ARENA_TYPE_DEAD 0xeeeeeeee
#else
#define ARENA_TYPE_USED 0
#define ARENA_TYPE_FREE 1
#define ARENA_TYPE_HEAD 2
#endif

#define MALLOC_CHUNK_MASK (_KLIBC_MALLOC_CHUNK_SIZE-1)

#define ARENA_SIZE_MASK (~(sizeof(struct arena_header)-1))

/*
 * This structure should be no more than twice the size of the
 * previous structure.
 */
struct free_arena_header {
    struct arena_header a;
    struct free_arena_header *next_free, *prev_free;
};

/*
 * Internal variable used by brk/sbrk
 */
extern char *__current_brk;
