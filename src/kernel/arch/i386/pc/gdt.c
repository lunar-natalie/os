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

#include <kernel/error.h>

/* GDT with one null descriptor, two ring 0 segments, two ring 3 segments, and
 * the TSS segment. */
#define GDT_LENGTH 6
static gdt_data_t gdt[GDT_LENGTH];
static gdt_entry_t *
    gdt_entries[GDT_LENGTH - 1]; /* GDT length minus null descriptor. */
static gdt_entry_t ring0_code;   /* Kernel code segment. */
static gdt_entry_t ring0_data;   /* Kernel data segment. */
static gdt_entry_t ring1_code;   /* Userspace code segment. */
static gdt_entry_t ring1_data;   /* Userspace data segment. */
static gdt_entry_t tss_entry;    /* Task state segment. */

const static gdt_data_t GDT_NULL = {};

void encode_gdt_entry(gdt_data_t * dest, gdt_entry_t const * source)
{
    if (source->limit > GDT_MAX_LIMIT) {
        kernel_error("Cannot encode GDT limit larger than 0x%x", GDT_MAX_LIMIT);
    }

    /* Limit */
    const uint32_t limit_value = (uint32_t) source->limit;
    dest->limit_low            = limit_value & 0xFFFF;       /* Bits 0-15 */
    dest->limit_high           = (limit_value >> 16) & 0x0F; /* Bits 16-19  */
    /* Base */
    const uint32_t base_value  = (uint32_t) source->base;
    dest->base_low             = base_value & 0xFFFFFF; /* Bits 0-24 */
    dest->base_high            = base_value >> 24;      /* Bits 24-31 */
    /* Access byte */
    dest->access               = source->access;
    /* Flags */
    dest->flags                = source->flags;
}

void gdt_init(void)
{
    /* Null descriptor */
    gdt[0] = GDT_NULL;

    /* Kernel code segment */
    ring0_code.base   = (uint32_t *) 0;
    ring0_code.limit  = (uint32_t *) 0xFFFFF;
    ring0_code.access = (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_E
                                   | ACCESS_BITS_S | ACCESS_BITS_P);
    ring0_code.flags  = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);
    gdt_entries[0]    = &ring0_code;

    /* Kernel data segment */
    ring0_data.base  = (uint32_t *) 0;
    ring0_data.limit = (uint32_t *) 0xFFFFF;
    ring0_data.access =
        (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_S | ACCESS_BITS_P);
    ring0_data.flags = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);
    gdt_entries[1]   = &ring0_data;

    /* Userspace code segment */
    ring1_code.base  = (uint32_t *) 0;
    ring1_code.limit = (uint32_t *) 0xFFFFF;
    ring1_code.access =
        (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_E | ACCESS_BITS_S
                   | ACCESS_BITS_DPL | ACCESS_BITS_P);
    ring1_code.flags = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);
    gdt_entries[2]   = &ring1_code;

    /* Userspace data segment */
    ring1_data.base  = (uint32_t *) 0;
    ring1_data.limit = (uint32_t *) 0xFFFFF;
    ring1_data.access =
        (uint8_t) (ACCESS_BITS_S | ACCESS_BITS_DPL | ACCESS_BITS_P);
    ring1_data.flags = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);
    gdt_entries[3]   = &ring1_data;

    /* Task state segment */
    tss_entry.base  = (uint32_t *) &tss;
    tss_entry.limit = (uint32_t *) sizeof(tss);
    tss_entry.access =
        (uint8_t) (ACCESS_BITS_A | ACCESS_BITS_E | ACCESS_BITS_P);
    tss_entry.flags = 0;
    gdt_entries[4]  = &tss_entry;

    /* Encode (skip null descriptor) */
    for (size_t i = 0; i < GDT_LENGTH - 1; ++i) {
        encode_gdt_entry(&gdt[i + 1], gdt_entries[i]);
    }

    load_gdt(gdt, GDT_LENGTH - 1);

    // flush_tss();
}
