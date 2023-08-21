/*
 * gdt.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/gdt.h>

#include <stddef.h>
#include <stdint.h>

#include <kernel/arch/i386/pc/tss.h>
#include <kernel/error.h>

/* GDT with one null descriptor, two ring 0 segments, two ring 3 segments, and
 * the TSS segment. */
static gdt_data_t       gdt[GDT_LENGTH];
/* Array of pointers to the filled GDT entries. Size is the full GDT length
 * minus the null descriptor. */
static gdt_entry_t *    gdt_entries[GDT_LENGTH - 1];
static gdt_entry_t      ring0_code;      /* Kernel code segment. */
static gdt_entry_t      ring0_data;      /* Kernel data segment. */
static gdt_entry_t      ring3_code;      /* Userspace code segment. */
static gdt_entry_t      ring3_data;      /* Userspace data segment. */
static gdt_entry_t      ring0_tss_entry; /* Task state segment. */
const static gdt_data_t GDT_NULL = {};

void gdt_init(tss_t const * ring0_tss)
{
    /* Null descriptor */
    gdt[0] = GDT_NULL;

    /* Kernel code segment */
    ring0_code.base   = 0;
    ring0_code.limit  = 0xFFFFF;
    ring0_code.access = (uint8_t) (ACCESS_BITS_P | ACCESS_BITS_S | ACCESS_BITS_E
                                   | ACCESS_BITS_RW);
    ring0_code.flags  = (uint8_t) (FLAG_BITS_G | FLAG_BITS_DB);
    gdt_entries[0]    = &ring0_code;

    /* Kernel data segment */
    ring0_data.base  = 0;
    ring0_data.limit = 0xFFFFF;
    ring0_data.access =
        (uint8_t) (ACCESS_BITS_P | ACCESS_BITS_S | ACCESS_BITS_RW);
    ring0_data.flags = (uint8_t) (FLAG_BITS_G | FLAG_BITS_DB);
    gdt_entries[1]   = &ring0_data;

    /* Userspace code segment */
    ring3_code.base  = 0;
    ring3_code.limit = 0xFFFFF;
    ring3_code.access =
        (uint8_t) (ACCESS_BITS_P | ACCESS_BITS_DPL_3 | ACCESS_BITS_S
                   | ACCESS_BITS_E | ACCESS_BITS_RW);
    ring3_code.flags = (uint8_t) (FLAG_BITS_G | FLAG_BITS_DB);
    gdt_entries[2]   = &ring3_code;

    /* Userspace data segment */
    ring3_data.base   = 0;
    ring3_data.limit  = 0xFFFFF;
    ring3_data.access = (uint8_t) (ACCESS_BITS_P | ACCESS_BITS_DPL_3
                                   | ACCESS_BITS_S | ACCESS_BITS_RW);
    ring3_data.flags  = (uint8_t) (FLAG_BITS_G | FLAG_BITS_DB);
    gdt_entries[3]    = &ring3_data;

    /* Task state segment
     * Note: the functions of some bits in the TSS descriptor differ
     * from that of the other GDT entry types. */
    ring0_tss_entry.base  = (uint32_t) ring0_tss;
    ring0_tss_entry.limit = sizeof(*ring0_tss);
    ring0_tss_entry.access =
        (uint8_t) (ACCESS_BITS_P   /* Required */
                   | ACCESS_BITS_E /* Indicates 32-bit */
                   | ACCESS_BITS_A /* System segment, therefore indicates TSS */
        );
    ring0_tss_entry.flags = 0;
    gdt_entries[4]        = &ring0_tss_entry;

    /* Encode (skip null descriptor) */
    for (size_t i = 0; i < GDT_LENGTH - 1; ++i) {
        encode_gdt_entry(&gdt[i + 1], gdt_entries[i]);
    }

    if (load_gdt(gdt, GDT_LENGTH - 1) != 0) {
        kernel_error("Failed to load GDT\n");
    }
}

void encode_gdt_entry(gdt_data_t * dest, gdt_entry_t const * source)
{
    /* Limit */
    if (source->limit > GDT_MAX_LIMIT) {
        kernel_error("Cannot encode GDT limit larger than 0x%x", GDT_MAX_LIMIT);
    }
    dest->limit_low  = source->limit & 0xFFFF;       /* Bits 0-15 */
    dest->limit_high = (source->limit >> 16) & 0x0F; /* Bits 16-19  */
    /* Base */
    dest->base_low   = source->base & 0xFFFFFF; /* Bits 0-24 */
    dest->base_high  = source->base >> 24;      /* Bits 24-31 */
    /* Access byte */
    dest->access     = source->access;
    /* Flags */
    dest->flags      = source->flags;
}
