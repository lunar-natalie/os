/*
 * main.c
 * Kernel entry point.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/tty.h>

#include <stddef.h>
#include <stdio.h>

#include <kernel/arch/i386/pc/vga.h>

void kernel_main(void)
{
    tty_init();
    printf("Hello, world!\n");
}
