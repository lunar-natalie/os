/*
 * vga.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/vga.h>

#include <stddef.h>
#include <stdint.h>
#include <string.h>

void vga_init(vga_t * vga)
{
    vga->row    = 0;
    vga->column = 0;
    vga->color  = make_vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga->buffer = (uint16_t *) VGA_BUFFER;
    for (size_t y = 0; y < VGA_HEIGHT; ++y) {
        for (size_t x = 0; x < VGA_WIDTH; ++x) {
            const size_t index = y * VGA_WIDTH + x;
            vga->buffer[index] = make_vga_entry(' ', vga->color);
        }
    }
}

void vga_set_color(vga_t * vga, uint8_t color)
{
    vga->color = color;
}

void vga_put_entry_at(
    vga_t * vga, char c, uint8_t color, size_t x, size_t y)
{
    vga->buffer[make_vga_index(x, y)] = make_vga_entry(c, color);
}

void vga_next_line(vga_t * vga)
{
    vga->column = 0;
    if (vga->row + 1 == VGA_HEIGHT) {
        vga_scroll(vga);
    }
    else {
        ++vga->row;
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
    const static uint16_t last_row = (VGA_HEIGHT - 1) * VGA_WIDTH;

    for (size_t y = 0; y < VGA_HEIGHT - 1; ++y) {
        memcpy((void *) (vga->buffer + (y * VGA_WIDTH)),
               (void *) (vga->buffer + ((y + 1) * VGA_WIDTH)),
               VGA_WIDTH);
    }

    for (size_t i = last_row; i < last_row + VGA_WIDTH; ++i) {
        vga->buffer[i] = 0;
    }
}

void vga_write(vga_t * vga, const char * s, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        vga_put_char(vga, s[i]);
    }
}

size_t vga_write_string(vga_t * vga, const char * s)
{
    size_t len = strlen(s);
    vga_write(vga, s, len);
    return len;
}
