/**
 * @file tss.h
 * @brief Task State Segment.
 */

/*
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ARCH_I386_PC_TSS_H
#define _KERNEL_ARCH_I386_PC_TSS_H

#include <stdint.h>

/* Task State Segment data structure. */
typedef struct tss_data {
    /**
     * Previous TSS. With hardware task switching, these form a backward linked
     * list.
     */
    uint32_t prev_tss;

    uint32_t esp0; /** Stack pointer to load when switching to kernel mode. */
    uint32_t ss0;  /** Stack segment to load when switching to kernel mode. */

    /* The following members are unused. */
    /* Note: esp and ss 1 and 2 are used when switching to rings 1 or 2. */

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
} __attribute__((packed)) tss_t;

/** @return Pointer to initialized kernel-mode TSS data. */
tss_t * tss_init_ring0();

/**
 * Loads the TSS into the Task Register.
 *
 * @param gdt_index Index of the TSS entry in the GDT.
 * @param rpl Requested privilege level.
 *
 * @note Must be called after the GDT has been loaded.
 */
extern void load_tss(unsigned int gdt_index, unsigned int rpl);

#endif /* _KERNEL_ARCH_I386_PC_TSS_H */
