/*
 * tty.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/tty.h>

#include <stddef.h>

#include <kernel/arch/i386/pc/vga.h>

static vga_t vga;

void tty_init(void)
{
    vga_init(&vga);
}

void tty_put_char(char c)
{
    vga_put_char(&vga, c);
}

size_t tty_write_string(const char * s)
{
    return vga_write_string(&vga, s);
}
