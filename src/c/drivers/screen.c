#include "screen.h"

unsigned short get_screen_offset(int col, int row) {
  return (row * MAX_COLS) + col;
}

void update_cursor(int col, int row) {
  unsigned short offset = get_screen_offset(col, row);
  set_cursor(offset);
}

unsigned short get_cursor() {
  unsigned short offset;
  // cursor LOW port to vga INDEX register
  port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_LOW);
  offset = (unsigned char) port_byte_in(REG_SCREEN_DATA) & 0xff;
  // cursor HIGH port to vga INDEX register
  port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_HIGH);
  offset += (unsigned char) (port_byte_in(REG_SCREEN_DATA)  >> 8) & 0xff;
  return offset;
}

void set_cursor(unsigned short offset) {
  // cursor LOW port to vga INDEX register
  port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_LOW);
  port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset & 0xff));
  // cursor HIGH port to vga INDEX register
  port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_HIGH);
  port_byte_out(REG_SCREEN_DATA, (unsigned char) ((offset >> 8) & 0xff));
}

/* Advance the text cursor, scrolling the video buffer if necessary. */ 
int handle_scrolling(unsigned short cursor_offset) {
  // If the cursor is within the screen, return it unmodified. 
  if (cursor_offset < MAX_ROWS * MAX_COLS) {
    return cursor_offset; 
  }

  /* Shuffle the rows back one. */ 
  int i;
  for (i = 1; i < MAX_ROWS; i++) {
    memory_copy(get_screen_offset(0, i) + get_screen_offset(0, i - 1) + VIDEO_ADDRESS, MAX_COLS); 
  }

  /* Blank the last line by setting all bytes to 0 */
  char* last_line = (char*) get_screen_offset(0, MAX_ROWS -1) + VIDEO_ADDRESS; 
  
  for (i = 0; i < MAX_COLS; i++) {
    last_line[i] = 0; 
  }
  
  // Move the offset back one row, such that it is now on the last 
  // row, rather than off the edge of the screen.
  cursor_offset -= MAX_COLS;
  // Return the updated cursor position.
  return cursor_offset; 
}

void print_at(char* message, int col, int row) {
  // Update the cursor if col and row not negative. 
  if (col >= 0 && row >= 0) {
    set_cursor(get_screen_offset(col, row)); 
  }

  // Loop through each char of the message and print it. 
  int i = 0;
  while(message[i] != 0) {
    print_char(message[i++], col, row, WHITE_ON_BLACK); 
  }
}

/* Print a char on the screen at col, row, or at cursor position */
void print_char(char character, int col, int row, char attribute_byte) {
  /* Create a byte (char) pointer to the start of video memory */ 
  unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
  
  /* If attribute byte is zero, assume the default style. */ 
  if (!attribute_byte) {
    attribute_byte = WHITE_ON_BLACK; 
  }

  /* Get the video memory offset for the screen location */ 
  int offset;
  
  /* If col and row are non-negative, use them for offset. */ 
  if (col >= 0 && row >= 0) {
    offset = get_screen_offset(col, row);
  /* Otherwise, use the current cursor position. */
  } else {
    offset = get_cursor(); 
  }
  
  // If we see a newline character, set offset to the end of 
  // current row, so it will be advanced to the first col
  // of the next row.
  if (character == '\n') {
    int rows = offset / MAX_COLS;
    offset = get_screen_offset(79, rows);
    // Otherwise, write the character and its attribute byte to 
    // video memory at our calculated offset.
  } else {
    vidmem[offset * 2] = character;
    vidmem[offset * 2 + 1] = attribute_byte; 
  }
  
  // Update the offset to the next character cell, which is 
  // two bytes ahead of the current cell.
  offset += 1;
  // Make scrolling adjustment, for when we reach the bottom // of the screen.
//  offset = handle_scrolling(offset);
  // Update the cursor position on the screen device.
  set_cursor(offset); 
}

void print(char* message) { 
  print_at(message , -1, -1);
}

void clear_screen() { 
  int row = 0;
  int col = 0;
  
  /* Loop through video memory and write blank characters. */ 
  for (row = 0; row < MAX_ROWS; row++) {
    for (col = 0; col < MAX_COLS; col++) { 
      print_char(' ', col, row, WHITE_ON_BLACK);
    } 
  }

  // Move the cursor back to the top left.
  update_cursor(0, 0);
}
