#include "low_level.h"

// From http://wiki.osdev.org/Inline_Assembly/Examples

uint32_t farpeek(uint16_t sel, void *off) {
    uint32_t ret;
    
    __asm__ ("push %%fs\n\t"
        "mov  %1, %%fs\n\t"
        "mov  %%fs:(%2), %0\n\t"
        "pop  %%fs"
        : "=r"(ret) /* output operands */
        : "g"(sel), "r"(off) /* input operands */
        );
    return ret;
}

void farpoke(uint16_t sel, void *off, uint8_t v) {
    __asm__("push %%fs\n\t"
        "mov  %0, %%fs\n\t"
        "movb %2, %%fs:(%1)\n\t"
        "pop %%fs"
        : /* no output operands */
        : "g"(sel), "r"(off), "r"(v) /* input operands */
        );
    /* TODO: Should "memory" be in the clobber list here? */
}