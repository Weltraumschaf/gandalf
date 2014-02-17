/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */

#ifndef __SYS_CDEFS_H
#define __SYS_CDEFS_H

#define __gandalf_libc 1

#if defined(__cplusplus)
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

/**
 * The \0 character.
 */
#define END_OF_STRING ((char) '\0')
/**
 * The\n character.
 */
#define NEW_LINE ((char) '\n')

/* number of bits in a byte */
#define NBBY    8

#endif /* __SYS_CDEFS_H */
