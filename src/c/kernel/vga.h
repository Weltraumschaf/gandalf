/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */

#ifndef __VGA_H_
#define __VGA_H_

#include <stdint.h>
#include "../libc/include/sys/types.h"

static const uint8_t COLOR_BLACK                = 0;
static const uint8_t COLOR_BLUE                 = 1;
static const uint8_t COLOR_GREEN                = 2;
static const uint8_t COLOR_CYAN                 = 3;
static const uint8_t COLOR_RED                  = 4;
static const uint8_t COLOR_MAGENTA              = 5;
static const uint8_t COLOR_BROWN                = 6;
static const uint8_t COLOR_LIGHT_GREY           = 7;
static const uint8_t COLOR_DARK_GREY            = 8;
static const uint8_t COLOR_LIGHT_BLUE           = 9;
static const uint8_t COLOR_LIGHT_GREEN          = 10;
static const uint8_t COLOR_LIGHT_CYAN           = 11;
static const uint8_t COLOR_LIGHT_RED            = 12;
static const uint8_t COLOR_LIGHT_MAGENTA        = 13;
static const uint8_t COLOR_LIGHT_BROWN          = 14;
static const uint8_t COLOR_WHITE                = 15;

/**
 * Characters per screen row.
 */
static const size_t VGA_WIDTH = 80;
/**
 * Lines per screen.
 */
static const size_t VGA_HEIGHT = 25;

/**
 * Address of memory mapped video memory.
 */
static uint16_t * const VGA_MEMORY = (uint16_t*) 0xB8000;

/**
 * Creates a combined color setting byte.
 *
 * @param foreground one of COLOR_* constants
 * @param background one of COLOR_* constants
 * @return the combiend byte
 */
uint8_t make_color(uint8_t foreground, uint8_t background);
/**
 * Combines color setting byte and character byte to word directly usable for video memory.
 *
 * @param character character to print
 * @param color color setting for character
 * @return video memory byte
 */
uint16_t make_vgaentry(char character, uint8_t color);

#endif /* __VGA_H_ */
