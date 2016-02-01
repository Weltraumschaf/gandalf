#include "low_level.h"

// From http://wiki.osdev.org/Inline_Assembly/Examples

void define_interupt_table(void *base, uint16_t size) {
    // https://en.wikipedia.org/wiki/Interrupt_descriptor_table
    struct {
        uint16_t length;
        uint32_t base;
    } __attribute__((packed)) IDTR;

    IDTR.length = size;
    IDTR.base = (uint32_t)base;

    __asm__ __volatile__("lidt (%0)"
                         :            /* no output operands */
                         : "p"(&IDTR) /* input operands */
                         );
}