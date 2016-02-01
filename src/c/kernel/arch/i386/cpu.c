#include "low_level.h"

// From http://wiki.osdev.org/Inline_Assembly/Examples

void cpuid(int code, uint32_t *a, uint32_t *d) {
    __asm__ __volatile__("cpuid"
                         : "=a"(*a), "=d"(*d) /* output operands */
                         : "0"(code)          /* input operands */
                         : "ebx", "ecx"       /* clobbered registers */
                         );
}

void rdtsc(uint32_t *upper, uint32_t *lower) {
    // TODO It may be better to return a struct instead of using pointers.
    __asm__ __volatile__("rdtsc"
                         : "=a"(*lower), "=d"(*upper) /* output operands */
                         );
}

unsigned long read_cr0(void) {
    unsigned long val;

    __asm__ __volatile__("mov %%cr0, %0"
                         : "=r"(val) /* output operands */
                         );

    return val;
}

void invlpg(void *m) {
    /*
     * Clobber memory to avoid optimizer re-ordering access before invlpg,
     * which may cause nasty bugs.
     */
    __asm__ __volatile__("invlpg %0"
                         :          /* no output operands */
                         : "m"(m)   /* input operands */
                         : "memory" /* clobbered memory */
                         );
}

void wrmsr(uint32_t msr_id, uint64_t msr_value) {
    __asm__ __volatile__("wrmsr"
                         :                             /* no output operands */
                         : "c"(msr_id), "A"(msr_value) /* input operands */
                         );
}

uint64_t rdmsr(uint32_t msr_id) {
    uint64_t msr_value;

    __asm__ __volatile__("rdmsr"
                         : "=A"(msr_value) /* output operands */
                         : "c"(msr_id)     /* input operands */
                         );

    return msr_value;
}

void halt() {
    __asm__("hlt");
}
