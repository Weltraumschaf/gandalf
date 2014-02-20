#ifndef __STDLIB_H_
#define __STDLIB_H_

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/**
 * The abort() function causes abnormal program termination to occur.
 */
void abort() __attribute__((__noreturn__));

__END_DECLS

#endif /* __STDLIB_H_ */
