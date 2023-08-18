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

void vga_init(struct vga * vga)
{
    vga->row    = 0;
    vga->column = 0;
    vga->color  = make_vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga->buffer = (uint16_t *) VGA_BUFFER;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            vga->buffer[index] = make_vga_entry(' ', vga->color);
        }
    }
}

void vga_setcolor(struct vga * vga, uint8_t color)
{
    vga->color = color;
}

void vga_putentryat(
    struct vga * vga, char c, uint8_t color, uint16_t x, uint16_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    vga->buffer[index] = make_vga_entry(c, color);
}

void vga_putchar(struct vga * vga, char c)
{
    vga_putentryat(vga, c, vga->color, vga->column, vga->row);
    if (++vga->column == VGA_WIDTH) {
        vga->column = 0;
        if (++vga->row == VGA_HEIGHT) {
            vga->row = 0;
        }
    }
}

void vga_write(struct vga * vga, const char * s, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        vga_putchar(vga, s[i]);
    }
}

void vga_writestring(struct vga * vga, const char * s)
{
    vga_write(vga, s, strlen(s));
}
