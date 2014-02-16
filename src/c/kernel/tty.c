#include "tty.h"
#include "vga.h"
#include "arch/i386/low_level.h"
#include "../libc/include/string.h"

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

void tty_clear() {
    for (size_t y = 0; y <= VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            tty_buffer[index] = make_vgaentry(BLANK, tty_color);
        }
    }
}

size_t tty_computeOffset(uint8_t row, uint8_t column) {
    size_t offset = row * VGA_WIDTH + column;

    if (offset >= MAX_OFFSET) {
        offset = 0;
    }

    return offset;
}

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
    tty_row        = 0;
    tty_column     = 0;
    tty_color      = DEFAULT_COLOR;
    tty_buffer     = VGA_MEMORY;
    tty_clear();
    tty_setCursor(tty_column, tty_row);
}

void tty_setColor(uint8_t color) {
    tty_color = color;
}

void tty_putEntryAt(char c, uint8_t color, size_t row, size_t column) {
    const size_t offset = tty_computeOffset(row, column);
    tty_buffer[offset] = make_vgaentry(c, color);
}

void tty_putChar(char c) {
    if (NEW_LINE == c) {
        tty_column = VGA_WIDTH - 1; // Move to end of column.
    } else {
        tty_putEntryAt(c, tty_color, tty_row, tty_column);
    }

    if (++tty_column == VGA_WIDTH) {
        tty_column = 0;

        if (++tty_row == VGA_HEIGHT) {
            tty_row = 0;
        }
    }

    tty_setCursor(tty_row, tty_column);
}

void tty_write(const char* data) {
    const size_t size = strlen(data);

    for (size_t i = 0; i < size; i++) {
        tty_putChar(data[i]);
    }
}

