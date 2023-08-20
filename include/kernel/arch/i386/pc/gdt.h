/*
 * gdt.h
 * Global Descriptor Table.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ARCH_I386_PC_GDT_H
#define _KERNEL_ARCH_I386_PC_GDT_H

#include <stdint.h>

enum access_bits {
    /* Present bit. Must be set for any valid segment. */
    ACCESS_BITS_P   = 0b10000000,
    /* Descriptor privellege level (ring 0-3). */
    ACCESS_BITS_DPL = 0b01100000,
    /* Descriptor type bit. Clear if system segment, set if code or data
     * segment. */
    ACCESS_BITS_S   = 0b00010000,
    /* Executable bit. */
    ACCESS_BITS_E   = 0b00001000,
    /* Direction/conforming bit.
     *
     * Direction bit for data selectors: if clear, the segment grows up; if set,
     * the segment grows down.
     *
     * Conforming bit for code selectors: if clear, the segment can only be
     * executed from the ring set in the DPL; if set, the segment can be
     * executed from any privellege level. */
    ACCESS_BITS_DC  = 0b00000100,
    /* Read-write bit. If clear, the segment is readable (code); if set, the
     * segment is writable (data). */
    ACCESS_BITS_RW  = 0b00000010,
    /* Accessed bit (set by CPU) */
    ACCESS_BITS_A   = 0b00000001
};

enum flag_bits {
    /* Granularity flag (scales segment limit). If clear, the limit is scaled in
     * 1 byte blocks; if set, the limit is scaled in 4K blocks. */
    FLAG_BITS_G        = 0b00001000,
    /* Size flag. If clear, the descriptor defines a 16-bit protected mode
     * segment; if set, the descriptor defines a 32-bit protected mode segment.
     */
    FLAG_BITS_DB       = 0b00000100,
    /* Long-mode code flag. If set, the descriptor defines a 64-bit code
     * segment; for all other segment types the flag should be clear. */
    FLAG_BITS_L        = 0b00000010,
    /* Reserved. */
    FLAG_BITS_RESERVED = 0b00000001
};

struct segment_descriptor {
    uint32_t * base;
    uint64_t * limit;
    uint8_t    access;
    uint8_t    flags;
};

typedef struct segment_descriptor segment_descriptor_t;

/* GDT entry bit-fields. */
struct gdt_entry {
    /* Limit bits 0-15 */
    unsigned int limit_low  : 16;
    /* Base bits 0-15 */
    unsigned int base_low   : 24;
    /* Access bits */
    unsigned int access     : 8;
    /* Limit bits 16-19  */
    unsigned int limit_high : 4;
    /* Only used in software; has no effect on hardware */
    unsigned int available  : 1;
    /* Flag bits */
    unsigned int flags      : 3;
    /* Base bits 24-31 */
    unsigned int base_high  : 8;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

void encode_gdt_entry(gdt_entry_t * dest, segment_descriptor_t const * source);

extern void load_gdt(gdt_entry_t * data);

void gdt_init(void);

const static uint64_t *  GDT_MAX_LIMIT  = (uint64_t *) 0xFFFFF;
const static gdt_entry_t GDT_ENTRY_NULL = {};

#endif /* _KERNEL_ARCH_I386_PC_GDT_H */
