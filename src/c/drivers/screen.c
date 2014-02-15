#include "screen.h"
#include "cursor.h"
#include "../include/string.h"

/* Advance the text cursor, scrolling the video buffer if necessary. */
int handle_scrolling(int cursor_offset) {
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
    int* last_line = (int*) get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;

    for (i = 0; i < MAX_COLS; i++) {
        last_line[i] = 0;
    }

    // Move the offset back one row, such that it is now on the last
    // row, rather than off the edge of the screen.
    cursor_offset -= MAX_COLS;
    // Return the updated cursor position.
    return cursor_offset;
}

void print_at(const char* message, int col, int row) {
    // Update the cursor if col and row not negative.
    if (col >= 0 && row >= 0) {
        set_cursor(get_screen_offset(col, row));
    }

    // Loop through each char of the message and print it.
    int i = 0;
    while (message[i] != 0) {
        print_char(message[i++], col, row, WHITE_ON_BLACK);
    }
}

/* Print a char on the screen at col, row, or at cursor position */
void print_char(char character, int col, int row, uint8_t attribute_byte) {
    /* Create a byte (char) pointer to the start of video memory */
    volatile char* vidmem = (volatile char*) VIDEO_ADDRESS;

    /* If attribute byte is zero, assume the default style. */
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    /* Get the video memory offset for the screen location */
    int offset;

    if (col < 0 && row < 0) {
        /* Use the current cursor position. */
        offset = get_cursor();
    } else {
        /* If col and row are non-negative, use them for offset. */
        offset = get_screen_offset(col, row);
    }

    if (character == '\n') {
        // If we see a newline character, set offset to the end of
        // current row, so it will be advanced to the first col
        // of the next row.
        int rows = offset / MAX_COLS;
        offset = get_screen_offset(MAX_COLS - 1, rows);
    } else {
        // Otherwise, write the character and its attribute byte to
        // video memory at our calculated offset.
        vidmem[offset * 2] = character;
        vidmem[offset * 2 + 1] = attribute_byte;
    }

    // Update the offset to the next character cell, which is
    // two bytes ahead of the current cell.
    offset += 1;
    // Make scrolling adjustment, for when we reach the bottom // of the screen.
    // offset = handle_scrolling(offset);
    // Update the cursor position on the screen device.
    set_cursor(offset);
}

void print(const char* message) {
    print_at(message, -1, -1);
}

void println(const char* message) {
   char* messageWithNewLine;

   messageWithNewLine = (char *) malloc(strlen(message) + 1);
   strcpy(messageWithNewLine, message);
   strcat(messageWithNewLine, (char *) '\n');

   print(messageWithNewLine);
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
