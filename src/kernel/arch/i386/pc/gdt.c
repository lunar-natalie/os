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

/* GDT with one null segment, two ring 0 segments, two ring 3 segments, TSS
 * segment (ring 0 segments) */
#define GDT_LENGTH 6
static gdt_entry_t gdt[GDT_LENGTH];

static uint16_t task_state[UINT16_MAX];

void encode_gdt_entry(gdt_entry_t * dest, segment_descriptor_t const * source)
{
    if (source->limit > GDT_MAX_LIMIT) {
        kernel_error("Cannot encode GDT limit larger than 0x%x", GDT_MAX_LIMIT);
    }

    /* Limit */
    const uint64_t limit_value = (uint64_t) source->limit;
    dest->limit_low            = limit_value & 0xFFFF;       /* Bits 0-15 */
    dest->limit_high           = (limit_value >> 16) & 0x0F; /* Bits 16-19  */

    /* Base */
    const uint32_t base_value = (uint32_t) source->base;
    dest->base_low            = base_value & 0xFFFFFF; /* Bits 0-24 */
    dest->base_high           = (base_value >> 24);    /* Bits 24-31 */

    /* Access byte */
    dest->access = source->access;

    /* Flags */
    dest->flags = source->flags;
}

void gdt_init(void)
{
    segment_descriptor_t desc[GDT_LENGTH - 1];

    /* Kernel code segment */
    desc[0].base   = (uint32_t *) 0;
    desc[0].limit  = (uint64_t *) 0xFFFFF;
    desc[0].access = (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_E | ACCESS_BITS_S
                                | ACCESS_BITS_P);
    desc[0].flags  = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);

    /* Kernel data segment */
    desc[1].base   = (uint32_t *) 0;
    desc[1].limit  = (uint64_t *) 0xFFFFF;
    desc[1].access = (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_S | ACCESS_BITS_P);
    desc[1].flags  = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);

    /* User code segment */
    desc[2].base   = (uint32_t *) 0;
    desc[2].limit  = (uint64_t *) 0xFFFFF;
    desc[2].access = (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_E | ACCESS_BITS_S
                                | ACCESS_BITS_DPL | ACCESS_BITS_P);
    desc[2].flags  = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);

    /* User data segment */
    desc[3].base  = (uint32_t *) 0;
    desc[3].limit = (uint64_t *) 0xFFFFF;
    desc[3].access =
        (uint8_t) (ACCESS_BITS_S | ACCESS_BITS_DPL | ACCESS_BITS_P);
    desc[3].flags = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);

    /* Task state segment */
    desc[4].base   = (uint32_t *) &task_state;
    desc[4].limit  = (uint64_t *) UINT16_MAX;
    desc[4].access = (uint8_t) (ACCESS_BITS_A | ACCESS_BITS_E | ACCESS_BITS_P);
    desc[4].flags  = 0;

    /* Encode */
    gdt[0] = GDT_ENTRY_NULL;
    for (uint8_t i = 1, j = 0; i < GDT_LENGTH * sizeof(uint8_t); ++i, ++j) {
        encode_gdt_entry(&gdt[i], &desc[j]);
    }

    load_gdt(gdt);
}
