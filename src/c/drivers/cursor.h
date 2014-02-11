#ifndef __CURSOR_H__ 
#define __CURSOR_H__ 

#include <stdint.h>

#define MAX_ROWS 25
#define MAX_COLS 80
#define MAX_OFFSET 2000

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5
#define CURSOR_OFFSET_HIGH 0x0e
#define CURSOR_OFFSET_LOW 0x0f

int get_screen_offset(int col, int row);
void update_cursor(int col, int row);
int get_cursor();
void set_cursor(int offset);

#endif
