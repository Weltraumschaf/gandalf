#include "low_level.h"

// From http://wiki.osdev.org/Inline_Assembly/Examples

void port_byte_out(uint16_t port, uint8_t val) {
    // TODO Is it wrong to use 'N' for the port? It's not a 8-bit constant.
    // TODO Should %1 be %w1?
    // TODO Is there any reason to force the use of eax and edx?
    __asm__ __volatile__("outb %0, %1"
                         :                      /* no output operands */
                         : "a"(val), "Nd"(port) /* input operands */
                         );
}

uint8_t port_byte_in(uint16_t port) {
    uint8_t ret;
    // TODO Is it wrong to use 'N' for the port? It's not a 8-bit constant.
    // TODO Should %1 be %w1?
    // TODO Is there any reason to force the use of eax and edx?
    __asm__ __volatile__("inb %1, %0"
                         : "=a"(ret)  /* output operands */
                         : "Nd"(port) /* input operands */
                         );

    return ret;
}

void io_wait(void) {
    /*
     * Port 0x80 is used for 'checkpoints' during POST.
     * The Linux kernel seems to think it is free for use :-/
     */
    // TODO Is there any reason why al is forced?
    __asm__ __volatile__("outb %%al, $0x80"
                         :        /* no output operands */
                         : "a"(0) /* input operands */
                         );
}