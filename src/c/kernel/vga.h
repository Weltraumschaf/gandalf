/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */

#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H
 
#include <stdint.h>
 
static const uint8_t COLOR_BLACK = 0;
static const uint8_t COLOR_BLUE = 1;
static const uint8_t COLOR_GREEN = 2;
static const uint8_t COLOR_CYAN = 3;
static const uint8_t COLOR_RED = 4;
static const uint8_t COLOR_MAGENTA = 5;
static const uint8_t COLOR_BROWN = 6;
static const uint8_t COLOR_LIGHT_GREY = 7;
static const uint8_t COLOR_DARK_GREY = 8;
static const uint8_t COLOR_LIGHT_BLUE = 9;
static const uint8_t COLOR_LIGHT_GREEN = 10;
static const uint8_t COLOR_LIGHT_CYAN = 11;
static const uint8_t COLOR_LIGHT_RED = 12;
static const uint8_t COLOR_LIGHT_MAGENTA = 13;
static const uint8_t COLOR_LIGHT_BROWN = 14;
static const uint8_t COLOR_WHITE = 15;
 
inline uint8_t make_color(uint8_t fg, uint8_t bg)
{
	return fg | bg << 4;
}
 
inline uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;
 
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
#endif /* _KERNEL_VGA_H */
