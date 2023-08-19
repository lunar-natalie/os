/*
 * vga.h
 * Video Graphics Adapter.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ARCH_I386_PC_VGA_H
#define _KERNEL_ARCH_I386_PC_VGA_H

#include <stddef.h>
#include <stdint.h>

struct vga {
    size_t     row;
    size_t     column;
    uint8_t    color;
    uint16_t * buffer;
};

static const uint16_t * VGA_BUFFER = (uint16_t *) 0xB8000;
static const size_t     VGA_WIDTH  = 80;
static const size_t     VGA_HEIGHT = 25;

/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK         = 0,
    VGA_COLOR_BLUE          = 1,
    VGA_COLOR_GREEN         = 2,
    VGA_COLOR_CYAN          = 3,
    VGA_COLOR_RED           = 4,
    VGA_COLOR_MAGENTA       = 5,
    VGA_COLOR_BROWN         = 6,
    VGA_COLOR_LIGHT_GREY    = 7,
    VGA_COLOR_DARK_GREY     = 8,
    VGA_COLOR_LIGHT_BLUE    = 9,
    VGA_COLOR_LIGHT_GREEN   = 10,
    VGA_COLOR_LIGHT_CYAN    = 11,
    VGA_COLOR_LIGHT_RED     = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN   = 14,
    VGA_COLOR_WHITE         = 15,
};

static inline uint8_t make_vga_color(enum vga_color foreground,
                                     enum vga_color background)
{
    return (uint8_t) (foreground | background << 4);
}

static inline uint16_t make_vga_entry(unsigned char data, uint8_t color)
{
    return (uint16_t) data | (uint16_t) color << 8;
}

static inline uint16_t make_vga_index(size_t x, size_t y)
{
    return y * VGA_WIDTH + x;
}

void vga_init(struct vga * vga);

void vga_set_color(struct vga * vga, uint8_t color);

void vga_put_entry_at(
    struct vga * vga, char c, uint8_t color, size_t x, size_t y);

void vga_put_char(struct vga * vga, char c);

void vga_scroll(struct vga * vga);

void vga_write(struct vga * vga, const char * s, size_t size);

size_t vga_write_string(struct vga * vga, const char * s);

#endif // _KERNEL_ARCH_I386_PC_VGA_H
