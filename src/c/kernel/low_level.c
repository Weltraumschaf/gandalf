#include "low_level.h"

// From http://wiki.osdev.org/Inline_Assembly/Examples

// Memory access

/*
 * Read a 8/16/32-bit value at a given memory location using another segment  
 * than the default C data segment. Unfortunately there is no constraint for 
 * manipulating segment registers directly, so issuing the mov <reg>, <segmentreg> 
 * manually is required. 
 */
uint32_t farpeekl(uint16_t sel, void* off) {
  uint32_t ret;
  asm ( "push %%fs\n\t"
        "mov  %1, %%fs\n\t"
        "mov  %%fs:(%2), %0\n\t"
        "pop  %%fs"
        : "=r"(ret) : "g"(sel), "r"(off) );
  return ret;
}

/*
 * Write a 8/16/32-bit value to a segment:offset address too. Note that much 
 * like in farpeek, this version of farpoke saves and restore the segment 
 * register used for the access. 
 */
void farpokeb(uint16_t sel, void* off, uint8_t v) {
  asm ( "push %%fs\n\t"
        "mov  %0, %%fs\n\t"
        "movb %2, %%fs:(%1)\n\t"
        "pop %%fs"
        : : "g"(sel), "r"(off), "r"(v) );
  /* TODO: Should "memory" be in the clobber list here? */
}

// I/O access

/*
 * Sends a 8/16/32-bit value on a I/O location. Traditional names are outb, 
 * outw and outl respectively. The a modifier enforces val to be placed in the 
 * eax register before the asm command is issued and Nd allows for one-byte 
 * constant values to be assembled as constants, freeing the edx register for 
 * other cases. 
 *
 * "a" (data) means: load EAX with data 
 * "d" (port) means: load EDX with port
 */
void port_byte_out(uint16_t port, uint8_t val) {
  asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
  /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
  /* TODO: Should %1 be %w1? */
  /* TODO: Is there any reason to force the use of eax and edx? */
}

/*
 * Receives a 8/16/32-bit value from an I/O location. Traditional names are inb, 
 * inw and inl respectively. 
 *
 * A handy C wrapper function that reads a byte from the specified port
 * "=a" (result) means: put AL register in variable RESULT when finished
 * "d" (port) means: load EDX with port
 */
uint8_t port_byte_in(uint16_t port) {
  uint8_t ret;
  asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
  /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
  /* TODO: Should %1 be %w1? */
  /* TODO: Is there any reason to force the use of eax and edx? */
  return ret;
}

/*
 * Forces the CPU to wait for an I/O operation to complete. only use this when 
 * there's nothing like a status register or an IRQ to tell you the info has 
 * been received. 
 */
void io_wait(void) {
  /* Port 0x80 is used for 'checkpoints' during POST. */
  /* The Linux kernel seems to think it is free for use :-/ */
  asm volatile ( "outb %%al, $0x80" : : "a"(0) );
  /* TODO: Is there any reason why al is forced? */
}

// Interrupt-related functions 

/*
 * Returns a true boolean value if irq are enabled for the CPU. 
 */
bool are_interrupts_enabled() {
  unsigned long flags;
  asm volatile ( "pushf\n\t"
                 "pop %0"
                 : "=g"(flags) );
  return flags & (1 << 9);
  return false;
}

/*
 * Define a new interrupt table. .
 */
void lidt(void* base, uint16_t size) {
  struct {
    uint16_t length;
    uint32_t base;
  } __attribute__((packed)) IDTR;

  IDTR.length = size;
  IDTR.base = (uint32_t) base;
  asm volatile ( "lidt (%0)" : : "p"(&IDTR) );
}

// CPU-related functions

/*
 * Request for CPU identification. See CPUID for more information. 
 *
 * GCC has a <cpuid.h> header you should use instead of this.
 */
void cpuid(int code, uint32_t* a, uint32_t* d) {
  asm volatile ( "cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx" );
}

/*
 * Read the current value of the CPU's time-stamp counter and store into EDX:EAX. 
 * The time-stamp counter contains the amount of clock ticks that have elapsed 
 * since the last CPU reset. The value is stored in a 64-bit MSR and is incremented 
 * after each clock cycle. 
 *
 * This can be used to find out how much time it takes to do certain functions, 
 * very useful for testing/benchmarking /etc. Note: This is only an approximation. 
 */
void rdtsc(uint32_t* upper, uint32_t* lower) {
  /* TODO: It may be better to return a struct instead of using pointers. */
  asm volatile ( "rdtsc" : "=a"(*lower), "=d"(*upper) );
}

/*
 * Read the value in a control register.
 */
unsigned long read_cr0(void) {
  unsigned long val;
  asm volatile ( "mov %%cr0, %0" : "=r"(val) );
  return val;
}

/*
 * Invalidates the TLB (Translation Lookaside Buffer) for one specific virtual 
 * address. The next memory reference for the page will be forced to re-read PDE 
 * and PTE from main memory. Must be issued every time you update one of those 
 * tables. The m pointer points to a logical address, not a physical or virtual 
 * one: an offset for your ds segment. 
 */
void invlpg(void* m) {
  /* Clobber memory to avoid optimizer re-ordering access before invlpg, 
     which may cause nasty bugs. */
  //asm volatile ( "invlpg (%0)" : : "m"(m) : "memory" );
}

/*
 * Write a 64-bit value to a MSR. The A constraint stands for concatenation of 
 * registers EAX and EDX.
 */
void wrmsr(uint32_t msr_id, uint64_t msr_value) {
  asm volatile ( "wrmsr" : : "c" (msr_id), "A" (msr_value) );
}

/*
 * Read a 64-bit value from a MSR. The A constraint stands for concatenation of 
 * registers EAX and EDX.
 */
uint64_t rdmsr(uint32_t msr_id) {
  uint64_t msr_value;
  asm volatile ( "rdmsr" : "=A" (msr_value) : "c" (msr_id) );
  return msr_value;
}
