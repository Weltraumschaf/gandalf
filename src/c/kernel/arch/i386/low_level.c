#include "low_level.h"

// From http://wiki.osdev.org/Inline_Assembly/Examples

void port_byte_out(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" 
        : /* no output operands */
        : "a"(val), "Nd"(port) /* input operands */
        );
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    /* TODO: Is there any reason to force the use of eax and edx? */
}

uint8_t port_byte_in(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" 
        : "=a"(ret) /* output operands */ 
        : "Nd"(port) /* input operands */
        );
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    /* TODO: Is there any reason to force the use of eax and edx? */
    return ret;
}

void io_wait(void) {
    /* Port 0x80 is used for 'checkpoints' during POST. */
    /* The Linux kernel seems to think it is free for use :-/ */
    asm volatile("outb %%al, $0x80" 
        : /* no output operands */ 
        : "a"(0) /* input operands */
        );
    /* TODO: Is there any reason why al is forced? */
}

bool are_interrupts_enabled() {
    unsigned long flags;
    asm volatile("pushf\n\t"
                 "pop %0"
                 : "=g"(flags) /* output operands */
                 );
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
    
    asm volatile("lidt (%0)" 
        : /* no output operands */ 
        : "p"(&IDTR) /* input operands */
        );
}

void cpuid(int code, uint32_t *a, uint32_t *d) {
    asm volatile("cpuid" 
        : "=a"(*a), "=d"(*d) /* output operands */
        : "0"(code) /* input operands */
        : "ebx", "ecx" /* clobbered registers */
        );
}

void rdtsc(uint32_t *upper, uint32_t *lower) {
    /* TODO: It may be better to return a struct instead of using pointers. */
    asm volatile("rdtsc" 
        : "=a"(*lower), "=d"(*upper) /* output operands */
        );
}

unsigned long read_cr0(void) {
    unsigned long val;
    
    asm volatile("mov %%cr0, %0" 
        : "=r"(val) /* output operands */
        );
    
    return val;
}

void invlpg(void *m) {
    /* Clobber memory to avoid optimizer re-ordering access before invlpg,
       which may cause nasty bugs. */
    asm volatile("invlpg %0" 
        : /* no output operands */
        : "m"(m) /* input operands */
        : "memory" /* clobbered registers */
        );
}

void wrmsr(uint32_t msr_id, uint64_t msr_value) {
    asm volatile("wrmsr" 
        : /* no output operands */
        : "c"(msr_id), "A"(msr_value) /* input operands */
        );
}

uint64_t rdmsr(uint32_t msr_id) {
    uint64_t msr_value;
    
    asm volatile("rdmsr" 
        : "=A"(msr_value) /* output operands */
        : "c"(msr_id) /* input operands */
        );
    
    return msr_value;
}

void halt() {
    asm("hlt");
}
