#include "tty.h"
#include "vga.h"
#include "arch/i386/low_level.h"
#include "../libc/include/string.h"

size_t tty_row = 0;
size_t tty_column = 0;
bool tty_autoScrolling = false;
uint8_t tty_color;
uint16_t* tty_buffer;

void tty_clearChar(uint8_t row, uint8_t column) {
    const size_t index = row * VGA_WIDTH + column;
    tty_buffer[index] = make_vgaentry(BLANK, tty_color);
}

void tty_clearRow(uint8_t row) {
    for (size_t column = 0; column < VGA_WIDTH; column++) {
        tty_clearChar(row, column);
    }
}

void tty_clear() {
    for (size_t row = 0; row < VGA_HEIGHT; row++) {
        tty_clearRow(row);
    }
}

size_t tty_computeOffset(uint8_t row, uint8_t column) {
    size_t offset = row * VGA_WIDTH + column;

    if (offset >= MAX_OFFSET) {
        offset = 0;
    }

    return offset;
}

// See http://wiki.osdev.org/Text_Mode_Cursor
void tty_setCursor(int row, int column) {
    size_t offset = tty_computeOffset(row, column);

    // cursor LOW port to vga INDEX register
    port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_LOW);
    port_byte_out(REG_SCREEN_DATA, (int) (offset & 0xff));
    // cursor HIGH port to vga INDEX register
    port_byte_out(REG_SCREEN_CTRL, CURSOR_OFFSET_HIGH);
    port_byte_out(REG_SCREEN_DATA, (int) ((offset >> 8) & 0xff));
}

void tty_initialize() {
    tty_row = 0;
    tty_column = 0;
    tty_color = DEFAULT_COLOR;
    tty_buffer = VGA_MEMORY;
    tty_clear();
    tty_setCursor(tty_column, tty_row);
}

void tty_setColor(uint8_t color) {
    tty_color = color;
}

void tty_setAutoScrolling(bool flag) {
    tty_autoScrolling = flag;
}

void tty_setEnableBlinkingCursor(bool flag) {

}

void tty_putEntryAt(char c, uint8_t color, size_t row, size_t column) {
    const size_t offset = tty_computeOffset(row, column);
    tty_buffer[offset] = make_vgaentry(c, color);
}

void tty_handleScrolling() {
    int row;

    for (row = 1; row < VGA_HEIGHT; ++row) {
        size_t dstOffset = tty_computeOffset(row - 1, 0);
        size_t srcOffset = tty_computeOffset(row, 0);

        memcpy(dstOffset + VGA_MEMORY, srcOffset + VGA_MEMORY, VGA_WIDTH * 2);
    }

    tty_clearRow(VGA_HEIGHT - 1); // Clear last line.
}

void tty_recalculatePosition() {
    if (++tty_column == VGA_WIDTH) {
        tty_column = 0;

        if (++tty_row == VGA_HEIGHT) {
            if (tty_autoScrolling) {
                tty_handleScrolling();
                tty_row = VGA_HEIGHT - 1;
            } else {
                tty_row = 0;
            }
        }
    }
}

void tty_putChar(char c) {
    if (NEW_LINE == c) {
        tty_column = VGA_WIDTH - 1; // Move to end of column.
    } else {
        tty_putEntryAt(c, tty_color, tty_row, tty_column);
    }

    tty_recalculatePosition();
    tty_setCursor(tty_row, tty_column);
}

void tty_write(const char* data) {
    const size_t size = strlen(data);

    for (size_t i = 0; i < size; i++) {
        tty_putChar(data[i]);
    }
}

