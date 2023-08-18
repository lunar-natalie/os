/*
 * main.c
 * Kernel entry point.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/tty.h>

void kernel_main(void)
{
    tty_init();
    tty_writestring("Hello, world!");
}
