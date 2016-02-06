/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */

#pragma once

#if defined(__cplusplus)

#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#define __THROW throw()

#else

#define __BEGIN_DECLS
#define __END_DECLS
#define __THROW

#endif

/**
 * The \0 character.
 */
#define END_OF_STRING ((char)'\0')
/**
 * The\n character.
 */
#define NEW_LINE ((char)'\n')

/* number of bits in a byte */
#define NBBY 8
