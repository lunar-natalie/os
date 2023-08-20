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
    ACCESS_BITS_A   = 0b00000001,
    ACCESS_BITS_RW  = 0b00000010,
    ACCESS_BITS_DC  = 0b00000100,
    ACCESS_BITS_E   = 0b00001000,
    ACCESS_BITS_S   = 0b00010000,
    ACCESS_BITS_DPL = 0b01100000,
    ACCESS_BITS_P   = 0b10000000
};

enum flag_bits {
    FLAG_BITS_RESERVED = 0b00000001,
    FLAG_BITS_L        = 0b00000010,
    FLAG_BITS_DB       = 0b00000100,
    FLAG_BITS_G        = 0b00001000,
};

struct segment_descriptor {
    uint32_t * base;
    uint64_t * limit;
    uint8_t    access;
    uint8_t    flags;
};

typedef struct segment_descriptor segment_descriptor_t;

void encode_gdt_entry(uint8_t * dest, segment_descriptor_t const * source);

extern void load_gdt(uint8_t * data);

void gdt_init(void);

const static uint64_t * GDT_MAX_LIMIT  = (uint64_t *) 0xFFFFF;
const static uint8_t    GDT_ENTRY_NULL = 0;

#endif /* _KERNEL_ARCH_I386_PC_GDT_H */
