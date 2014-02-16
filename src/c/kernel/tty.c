#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../libc/include/string.h"
#include "vga.h"

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

void tty_clear() {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            tty_buffer[index] = make_vgaentry(' ', tty_color);
        }
    }
}

void tty_initialize() {
    tty_row        = 0;
    tty_column     = 0;
    tty_color      = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
    tty_buffer     = VGA_MEMORY;
    tty_clear();
}

void tty_setcolor(uint8_t color) {
    tty_color = color;
}

void tty_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    tty_buffer[index] = make_vgaentry(c, color);
}

void tty_putchar(char c) {
    tty_putentryat(c, tty_color, tty_column, tty_row);

    if (++tty_column == VGA_WIDTH) {
        tty_column = 0;

        if (++tty_row == VGA_HEIGHT) {
            tty_row = 0;
        }
    }
}

void tty_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        tty_putchar(data[i]);
    }
}

void tty_writestring(const char* data) {
    tty_write(data, strlen(data));
}
