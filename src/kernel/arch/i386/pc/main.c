/*
 * main.c
 * Kernel entry point for i386-pc.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/gdt.h>
#include <kernel/tty.h>

#include <stdio.h>

void kernel_main(void)
{
    tty_init();

    printf("init\n");

    gdt_init();

    printf("ready\n");
}
