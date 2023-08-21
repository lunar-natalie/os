/*
 * main.c
 * Kernel entry point for i386-pc.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/gdt.h>
#include <kernel/arch/i386/pc/tss.h>
#include <kernel/tty.h>

#include <stdio.h>

void kernel_main(void)
{
    static tss_t * ring0_tss;

    tty_init();

    printf("init\n");

    ring0_tss = tss_init_ring0();     /* Initialize kernel TSS */
    gdt_init(ring0_tss);              /* Initialize GDT */
    load_tss(GDT_RING0_TSS_INDEX, 0); /* Load kernel TSS */

    printf("ready\n");
}
