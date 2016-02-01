#include "low_level.h"

// From http://wiki.osdev.org/Inline_Assembly/Examples

uint32_t farpeekl(uint16_t sel, void *off) {
    uint32_t ret;
    asm("push %%fs\n\t"
        "mov  %1, %%fs\n\t"
        "mov  %%fs:(%2), %0\n\t"
        "pop  %%fs"
        : "=r"(ret)
        : "g"(sel), "r"(off));
    return ret;
}

void farpokeb(uint16_t sel, void *off, uint8_t v) {
    asm("push %%fs\n\t"
        "mov  %0, %%fs\n\t"
        "movb %2, %%fs:(%1)\n\t"
        "pop %%fs"
        :
        : "g"(sel), "r"(off), "r"(v));
    /* TODO: Should "memory" be in the clobber list here? */
}

void port_byte_out(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    /* TODO: Is there any reason to force the use of eax and edx? */
}

uint8_t port_byte_in(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    /* TODO: Is there any reason to force the use of eax and edx? */
    return ret;
}

void io_wait(void) {
    /* Port 0x80 is used for 'checkpoints' during POST. */
    /* The Linux kernel seems to think it is free for use :-/ */
    asm volatile("outb %%al, $0x80" : : "a"(0));
    /* TODO: Is there any reason why al is forced? */
}

bool are_interrupts_enabled() {
    unsigned long flags;
    asm volatile("pushf\n\t"
                 "pop %0"
                 : "=g"(flags));
    return flags & (1 << 9);
    return false;
}

void lidt(void *base, uint16_t size) {
    struct {
        uint16_t length;
        uint32_t base;
    } __attribute__((packed)) IDTR;

    IDTR.length = size;
    IDTR.base = (uint32_t)base;
    asm volatile("lidt (%0)" : : "p"(&IDTR));
}

void cpuid(int code, uint32_t *a, uint32_t *d) {
    asm volatile("cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx");
}

void rdtsc(uint32_t *upper, uint32_t *lower) {
    /* TODO: It may be better to return a struct instead of using pointers. */
    asm volatile("rdtsc" : "=a"(*lower), "=d"(*upper));
}

unsigned long read_cr0(void) {
    unsigned long val;
    asm volatile("mov %%cr0, %0" : "=r"(val));
    return val;
}

void invlpg(void *m) {
    /* Clobber memory to avoid optimizer re-ordering access before invlpg,
       which may cause nasty bugs. */
    //asm volatile("invlpg (%0)" : : "m"(m) : "memory" );
}

void wrmsr(uint32_t msr_id, uint64_t msr_value) {
    asm volatile("wrmsr" : : "c"(msr_id), "A"(msr_value));
}

uint64_t rdmsr(uint32_t msr_id) {
    uint64_t msr_value;
    asm volatile("rdmsr" : "=A"(msr_value) : "c"(msr_id));
    return msr_value;
}

void halt() {
    asm("hlt");
}
