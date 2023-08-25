/**
 * @file vga.h
 * @brief Video Graphics Adapter.
 */

/*
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ARCH_I386_PC_VGA_H
#define _KERNEL_ARCH_I386_PC_VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

/** Text mode VGA info object. */
typedef struct vga {
    size_t     row;
    size_t     column;
    uint8_t    color;
    uint16_t * buffer;
} vga_t;

/** Hardware text mode color constants. */
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

static inline uint16_t make_vga_index(uint8_t x, uint8_t y)
{
    return y * VGA_WIDTH + x;
}

/**
 * Initializes the VGA text mode.
 *
 * @param vga Pointer to the VGA driver data structure.
 */
void vga_init(vga_t * vga);

void vga_set_color(vga_t * vga, uint8_t color);

void vga_put_entry_at(vga_t * vga, char c, uint8_t color, uint8_t x, uint8_t y);

void vga_put_char(vga_t * vga, char c);

/** Scrolls the VGA buffer by 1 line, in software. */
void vga_scroll(vga_t * vga);

void vga_write(vga_t * vga, const char * s, size_t length);

size_t vga_write_string(vga_t * vga, const char * s);

#endif /* _KERNEL_ARCH_I386_PC_VGA_H */
