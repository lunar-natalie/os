/*
 * tss.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/tss.h>

#include <stdint.h>
#include <string.h>

static tss_t ring0_tss;

extern uint32_t _boot_ss0;
extern uint32_t _boot_esp0;

tss_t * tss_init_ring0()
{
    memset(&ring0_tss, 0, sizeof(tss_t)); /* Clear data */
    ring0_tss.ss0  = _boot_ss0;           /* Kernel stack segment */
    ring0_tss.esp0 = _boot_esp0;          /* Kernel stack pointer */
    return &ring0_tss;
}
