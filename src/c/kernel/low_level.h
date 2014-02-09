#ifndef __LOW_LEVEL_H_INCLUDED__ 
#define __LOW_LEVEL_H_INCLUDED__

#include <stdint.h>
  
void port_byte_out(uint16_t port, uint8_t val);
uint8_t port_byte_in(uint16_t port);

#endif
