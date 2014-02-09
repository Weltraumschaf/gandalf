#ifndef __LOW_LEVEL_H_INCLUDED__ 
#define __LOW_LEVEL_H_INCLUDED__

#include <stdint.h>
#include <stdbool.h>

// Memory access
uint32_t farpeekl(uint16_t sel, void* off);
void farpokeb(uint16_t sel, void* off, uint8_t v);

// I/O access
void port_byte_out(uint16_t port, uint8_t val);
uint8_t port_byte_in(uint16_t port);
void io_wait(void);

// Interrupt-related functions 
bool are_interrupts_enabled();
void lidt(void* base, uint16_t size);

// CPU-related functions
void cpuid(int code, uint32_t* a, uint32_t* d);
void rdtsc(uint32_t* upper, uint32_t* lower);
unsigned long read_cr0(void);
void invlpg(void* m);
void wrmsr(uint32_t msr_id, uint64_t msr_value);
uint64_t rdmsr(uint32_t msr_id);

#endif
