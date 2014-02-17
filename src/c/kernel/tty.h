/*
 * From http://wiki.osdev.org/User:Sortie/Meaty_Skeleton
 */

#ifndef __TTY_H_
#define __TTY_H_

/*
 * This is the kernel API to access the terminal.
 *
 * The terminal is a 80 x 24 VGA console.
 *
 *         row
 * col:           0      1      2        78     79                   offset
 * 0xb8000  0  [00,00][01,00][02,00]...[78,00][79,00] 160 0xa0 bytes    79
 * 0xb80a0  1  [00,01][01,01][02,01]...[78,01][79,01]                  158
 * 0xb8140  2  [00,02][01,02][02,02]...[78,02][79,02]                  237
 *                                  ...
 * 0xb80a0 24  [00,24][01,24][02,24]...[78,24][79,24]                 1896
 * 0xb8fa0 25  [00,25][01,25][02,25]...[78,25][79,25]                 1975
 *
 * offset = ( col + row * MAX_COLS) * 2
 *
 * [00,00] -> ( 0 + 0 * 80) * 2 =   0
 * [01,00] -> ( 1 + 0 * 80) * 2 =   2
 * [02,00] -> ( 2 + 0 * 80) * 2 =   4
 * [03,00] -> ( 3 + 0 * 80) * 2 =   6
 * [04,00] -> ( 4 + 0 * 80) * 2 =   8
 *               ...
 * [78,00] -> (78 + 0 * 80) * 2 = 156
 * [79,00] -> (79 + 0 * 80) * 2 = 158
 * [00,01] -> ( 0 + 1 * 80) * 2 = 160
 * [01,01] -> ( 1 + 1 * 80) * 2 = 162
 * [02,01] -> ( 2 + 1 * 80) * 2 = 164
 * [03,01] -> ( 3 + 1 * 80) * 2 = 166
 * [04,01] -> ( 4 + 1 * 80) * 2= 168
 *               ...
 * [78,01] -> (78 + 1 * 80) * 2 = 316
 * [79,01] -> (79 + 1 * 80) * 2 = 318
 * [00,02] -> ( 0 + 2 * 80) * 2 = 320
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "vga.h"

/**
 * Maximum offset in video memory.
 */
static const size_t MAX_OFFSET = 2000;

/**
 * Register port address for screen control.
 */
static const uint16_t REG_SCREEN_CTRL   = 0x3d4;
/**
 * Register port address for screen data.
 */
static const uint16_t REG_SCREEN_DATA   = 0x3d5;
/**
 * High byte offset for cursor position.
 */
static const uint8_t CURSOR_OFFSET_HIGH = 0x0e;
/**
 * Low byte offset for cursor position.
 */
static const uint8_t CURSOR_OFFSET_LOW  = 0x0f;

/**
 * Used to clear screen.
 */
static const char BLANK = ' ';

/**
 * Set all terminal settings (color, cursor position etc) to initial values and clears screen.
 */
void tty_initialize();
/**
 * Print empty characters onto the whole screen.
 */
void tty_clear();
/**
 * This function turn auto scrolling off and on.
 *
 * Auto scrolling means that the terminal shift all rows one up
 * if last rows columns were exceeded.
 *
 * Auto scrolling is off by default.
 *
 * @param flag true to turn on, false to turn off
 */
void tty_setAutoScrolling(bool flag);
void tty_setEnableBlinkingCursor(bool flag);
/**
 * Set the current terminal color.
 *
 * Use make_color() from vga.h to create color byte.
 *
 * @param color byte with high nibble as background and low nibble as foreground
 */
void tty_setColor(uint8_t color);
/**
 * Set the cursor on the screen.
 *
 * @param row to position the cursor
 * @param column to position the cursor
 */
void tty_setCursor(int row, int column);
/**
 * Put given character at current cursor position.
 *
 * Handles also wrap around to next row if end of row reached or '\n' input.
 *
 * @param c character to put on terminal
 */
void tty_putChar(char c);
/**
 * Write given string at current cursor position.
 *
 * Handles also wrap around to next row if end of row reached or '\n' input.
 *
 * @param data string to write on terminal
 */
void tty_write(const char* data);

#endif /* __TTY_H_ */
