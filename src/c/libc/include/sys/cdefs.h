#ifndef __SYS_CDEFS_H
#define __SYS_CDEFS_H
 
#define __myos_libc 1
 
#if defined(__cplusplus)
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif
 
#endif /* __SYS_CDEFS_H */
