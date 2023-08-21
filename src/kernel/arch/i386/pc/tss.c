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

static tss_t tss;

extern uint32_t   _boot_ss0;
extern uint32_t * _boot_esp0;

tss_t * tss_init()
{
    memset(&tss, 0, sizeof(tss));     /* Clear data */
    tss.ss0  = _boot_ss0;             /* Kernel stack segment */
    tss.esp0 = (uint32_t) _boot_esp0; /* Kernel stack pointer */
    return &tss;
}
