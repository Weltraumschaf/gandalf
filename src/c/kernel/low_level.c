
#include "low_level.h"

/*
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