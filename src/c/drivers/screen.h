#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdint.h>
#include "cursor.h"

/*
          row
  col:           0      1      2        78     79                   offset
  0xb8000  0  [00,00][01,00][02,00]...[78,00][79,00] 160 0xa0 bytes    79
  0xb80a0  1  [00,01][01,01][02,01]...[78,01][79,01]                  158
  0xb8140  2  [00,02][01,02][02,02]...[78,02][79,02]                  237
                                   ...
  0xb80a0 24  [00,24][01,24][02,24]...[78,24][79,24]                 1896
  0xb8fa0 25  [00,25][01,25][02,25]...[78,25][79,25]                 1975

  offset = ( col + row * MAX_COLS) * 2

  [00,00] -> ( 0 + 0 * 80) * 2 =   0
  [01,00] -> ( 1 + 0 * 80) * 2 =   2
  [02,00] -> ( 2 + 0 * 80) * 2 =   4
  [03,00] -> ( 3 + 0 * 80) * 2 =   6
  [04,00] -> ( 4 + 0 * 80) * 2 =   8
                ...
  [78,00] -> (78 + 0 * 80) * 2 = 156
  [79,00] -> (79 + 0 * 80) * 2 = 158
  [00,01] -> ( 0 + 1 * 80) * 2 = 160
  [01,01] -> ( 1 + 1 * 80) * 2 = 162
  [02,01] -> ( 2 + 1 * 80) * 2 = 164
  [03,01] -> ( 3 + 1 * 80) * 2 = 166
  [04,01] -> ( 4 + 1 * 80) * 2= 168
                ...
  [78,01] -> (78 + 1 * 80) * 2 = 316
  [79,01] -> (79 + 1 * 80) * 2 = 318
  [00,02] -> ( 0 + 2 * 80) * 2 = 320

 */
#define VIDEO_ADDRESS 0xb8000

// Attribute byte for our default colour scheme.
#define WHITE_ON_BLACK 0x0f

void print_char(char character, int col, int row, uint8_t attribute_byte);
void clear_screen();
void print(const char* message);

#endif
