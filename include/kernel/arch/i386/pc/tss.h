/*
 * tss.h
 * Task State Segment.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ARCH_I386_PC_TSS_H
#define _KERNEL_ARCH_I386_PC_TSS_H

#include <stdint.h>

/* Task State Segment. */
struct tss {
    uint32_t prev_tss; /* Previous TSS. With hardware task switching, these form
                          a backward linked list. */
    uint32_t esp0;     /* Stack pointer to load when changing to kernel mode. */
    uint32_t ss0;      /* Stack segment to load when changing to kernel mode. */

    /* Unused. */
    /* esp and ss 1 and 2 are used when switching to rings 1 or 2. */
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} __attribute__((packed));

typedef struct tss tss_t;

extern void flush_tss(void);

static tss_t tss;

#endif /* _KERNEL_ARCH_I386_PC_TSS_H */
