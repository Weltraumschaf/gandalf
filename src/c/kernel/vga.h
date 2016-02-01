/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */
#pragma once

#include <sys/cdefs.h>
#include <stddef.h>
#include <stdint.h>

__BEGIN_DECLS

static const uint8_t COLOR_BLACK = 0x00;
static const uint8_t COLOR_BLUE = 0x01;
static const uint8_t COLOR_GREEN = 0x02;
static const uint8_t COLOR_CYAN = 0x03;
static const uint8_t COLOR_RED = 0x04;
static const uint8_t COLOR_MAGENTA = 0x05;
static const uint8_t COLOR_BROWN = 0x06;
static const uint8_t COLOR_LIGHT_GREY = 0x07;
static const uint8_t COLOR_DARK_GREY = 0x08;
static const uint8_t COLOR_LIGHT_BLUE = 0x09;
static const uint8_t COLOR_LIGHT_GREEN = 0x0a;
static const uint8_t COLOR_LIGHT_CYAN = 0x0b;
static const uint8_t COLOR_LIGHT_RED = 0x0c;
static const uint8_t COLOR_LIGHT_MAGENTA = 0x0d;
static const uint8_t COLOR_LIGHT_BROWN = 0x0e;
static const uint8_t COLOR_WHITE = 0x0f;

static const uint8_t DEFAULT_COLOR =
    0x1e; // BG: COLOR_BLUE, FG: COLOR_LIGHT_BROWN
static const uint8_t DEFAULT_COLOR_INVERTED =
    0xe1; // BG: COLOR_LIGHT_BROWN, FG: COLOR_BLUE

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
static uint16_t *const VGA_MEMORY = (uint16_t *)0xB8000;

/**
 * Creates a combined color setting byte.
 *
 * @param foreground one of COLOR_* constants
 * @param background one of COLOR_* constants
 * @return the combiend byte
 */
uint8_t make_color(uint8_t foreground, uint8_t background);
/**
 * Combines color setting byte and character byte to word directly usable for
 * video memory.
 *
 * @param character character to print
 * @param color color setting for character
 * @return video memory byte
 */
uint16_t make_vgaentry(char character, uint8_t color);

__END_DECLS
