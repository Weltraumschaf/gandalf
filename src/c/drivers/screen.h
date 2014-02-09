#ifndef __SCREEN_H_INCLUDED__ 
#define __SCREEN_H_INCLUDED__ 

/*
          row
  col:           0      1      2        78     79
  0xb8000  0  [00,00][01,00][02,00]...[78,00][79,00] 160 0xa0 bytes
  0xb80a0  1  [00,01][01,01][02,01]...[78,01][79,01]
  0xb8140  2  [00,02][01,02][02,02]...[78,02][79,02]
                                   ...
  0xb80a0 24  [00,24][01,24][02,24]...[78,24][79,24]
  0xb8fa0 25  [00,25][01,25][02,25]...[78,25][79,25]

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

#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte for our default colour scheme.
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5
#define CURSOR_OFFSET_HIGH 0x0e
#define CURSOR_OFFSET_LOW 0x0f

void print_char(char character, int col, int row, char attribute_byte);
void clear_screen();
unsigned short get_screen_offset(int col, int row);
void update_cursor(int col, int row);
unsigned short get_cursor();
void set_cursor(unsigned short offset);

#endif
