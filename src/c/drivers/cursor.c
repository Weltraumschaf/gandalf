#include "cursor.h"
#include "low_level.h"

int get_screen_offset(int col, int row) {
  if (col >= MAX_COLS) {
    col = MAX_COLS - 1;
  }
  
  if (row >= MAX_ROWS) {
    row = MAX_ROWS - 1;
  }
  
  return col + row * MAX_COLS;
}

void update_cursor(int col, int row) {
  set_cursor(get_screen_offset(col, row));
}

int get_cursor() {
  int offset;

  // cursor LOW port to vga INDEX register
  port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_LOW);
  offset = (int) (port_byte_in(REG_SCREEN_DATA) & 0xff);
  // cursor HIGH port to vga INDEX register
  port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_HIGH);
  offset += (int) ((port_byte_in(REG_SCREEN_DATA) &0xff) << 8);

  return offset;
}

void set_cursor(int offset) {
  if (offset >= MAX_OFFSET) {
    offset = 0;
  }
  
  // cursor LOW port to vga INDEX register
  port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_LOW);
  port_byte_out(REG_SCREEN_DATA, (int) (offset & 0xff));
  // cursor HIGH port to vga INDEX register
  port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_HIGH);
  port_byte_out(REG_SCREEN_DATA, (int) ((offset >> 8) & 0xff));
}
