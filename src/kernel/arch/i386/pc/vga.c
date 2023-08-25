/*
 * vga.c
 *
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/vga.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

static uint16_t * const VGA_BUFFER = (uint16_t *) 0xB8000;

void vga_init(vga_t * vga)
{
    vga->row    = 0;
    vga->column = 0;
    vga->color  = make_vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga->buffer = VGA_BUFFER;
    for (uint8_t y = 0; y < VGA_HEIGHT; ++y) {
        for (uint8_t x = 0; x < VGA_WIDTH; ++x) {
            vga->buffer[make_vga_index(x, y)] =
                make_vga_entry('\0', vga->color);
        }
    }
}

void vga_set_color(vga_t * vga, uint8_t color)
{
    vga->color = color;
}

void vga_put_entry_at(vga_t * vga, char c, uint8_t color, uint8_t x, uint8_t y)
{
    vga->buffer[make_vga_index(x, y)] = make_vga_entry(c, color);
}

void vga_next_line(vga_t * vga)
{
    vga->column = 0;
    if (vga->row < VGA_HEIGHT - 1) {
        ++vga->row;
    }
    else {
        vga_scroll(vga);
    }
}

void vga_put_char(vga_t * vga, char c)
{
    if (c == '\n') {
        vga_next_line(vga);
    }
    else {
        vga_put_entry_at(vga, c, vga->color, vga->column, vga->row);
        if (++vga->column == VGA_WIDTH) {
            vga_next_line(vga);
        }
    }
}

void vga_scroll(vga_t * vga)
{
    static const uint16_t last_row = (VGA_HEIGHT - 1) * VGA_WIDTH;

    /* Copy each character in each row to the row after, until the final row has
     * been reached. */
    for (uint8_t y = 0; y < VGA_HEIGHT - 1; ++y) {
        memcpy((void *) (vga->buffer + (y * VGA_WIDTH)),
               (void *) (vga->buffer + ((y + 1) * VGA_WIDTH)),
               VGA_WIDTH);
    }

    /* Clear the last row. */
    for (uint16_t i = last_row; i < last_row + VGA_WIDTH; ++i) {
        vga->buffer[i] = 0;
    }
}

void vga_write(vga_t * vga, const char * s, size_t length)
{
    for (size_t i = 0; i < length; ++i) {
        vga_put_char(vga, s[i]);
    }
}

size_t vga_write_string(vga_t * vga, const char * s)
{
    size_t len = strlen(s);
    vga_write(vga, s, len);
    return len;
}
