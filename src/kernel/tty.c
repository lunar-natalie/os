/*
 * tty.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/tty.h>

#include <kernel/arch/i386/pc/vga.h>

struct vga vga;

void tty_init(void)
{
    vga_init(&vga);
}

void tty_writestring(const char * s)
{
    vga_writestring(&vga, s);
}
