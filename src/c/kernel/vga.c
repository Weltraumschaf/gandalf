/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */
#include "vga.h"

uint8_t make_color(uint8_t foreground, uint8_t background) {
    return foreground | background << 4;
}

uint16_t make_vgaentry(char character, uint8_t color) {
    uint16_t c16 = character;
    uint16_t color16 = color;

    return c16 | color16 << 8;
}
