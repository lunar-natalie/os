/*
 * gdt.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/gdt.h>

#include <limits.h>
#include <stdint.h>

#include <kernel/error.h>

static uint8_t  gdt_flat[6];
static uint16_t task_state[UINT16_MAX];

void encode_gdt_entry(uint8_t * dest, struct segment_descriptor const * source)
{
    if (source->limit > GDT_MAX_LIMIT) {
        kernel_error("Cannot encode GDT limit larger than %d", GDT_MAX_LIMIT);
    }

    /* Limit */
    const uint64_t limit_value = (uint64_t) source->limit;

    dest[0] = (uint8_t) (limit_value & 0xFF);         /* Bits 0-7 */
    dest[1] = (uint8_t) ((limit_value >> 8) & 0xFF);  /* Bits 8-15 */
    dest[6] = (uint8_t) ((limit_value >> 16) & 0x0F); /* Bits 16-19  */

    /* Base */
    const uint32_t base_value = (uint32_t) source->base;

    dest[2] = (uint8_t) (base_value & 0xFF);         /* Bits 0-7 */
    dest[3] = (uint8_t) ((base_value >> 8) & 0xFF);  /* Bits 8-15 */
    dest[4] = (uint8_t) ((base_value >> 16) & 0xFF); /* Bits 16-23 */
    dest[7] = (uint8_t) ((base_value >> 24) & 0xFF); /* Bits 24-31 */

    /* Access byte */
    dest[5] = source->access;

    /* Flags */
    dest[6] |= source->flags << 4; /* Bits 0-3 */
}

void gdt_init(void)
{
    struct segment_descriptor kcs; /* Kernel code segment */
    struct segment_descriptor kds; /* Kernel data segment */
    struct segment_descriptor ucs; /* User code segment */
    struct segment_descriptor uds; /* User data segment */
    struct segment_descriptor tss; /* Task state segment */

    kcs.base   = (uint32_t *) 0;
    kcs.limit  = (uint64_t *) 0xFFFFF;
    kcs.access = (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_E | ACCESS_BITS_S
                            | ACCESS_BITS_P);
    kcs.flags  = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);

    kds.base   = (uint32_t *) 0;
    kds.limit  = (uint64_t *) 0xFFFFF;
    kds.access = (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_S | ACCESS_BITS_P);
    kds.flags  = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);

    ucs.base   = (uint32_t *) 0;
    ucs.limit  = (uint64_t *) 0xFFFFF;
    ucs.access = (uint8_t) (ACCESS_BITS_RW | ACCESS_BITS_E | ACCESS_BITS_S
                            | ACCESS_BITS_DPL | ACCESS_BITS_P);
    ucs.flags  = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);

    uds.base   = (uint32_t *) 0;
    uds.limit  = (uint64_t *) 0xFFFFF;
    uds.access = (uint8_t) (ACCESS_BITS_S | ACCESS_BITS_DPL | ACCESS_BITS_P);
    uds.flags  = (uint8_t) (FLAG_BITS_DB | FLAG_BITS_G);

    tss.base   = (uint32_t *) &task_state;
    tss.limit  = (uint64_t *) UINT16_MAX;
    tss.access = (uint8_t) (ACCESS_BITS_A | ACCESS_BITS_E | ACCESS_BITS_P);
    tss.flags  = 0;

    gdt_flat[0] = GDT_ENTRY_NULL;
    encode_gdt_entry(gdt_flat + 8, &kcs);
    encode_gdt_entry(gdt_flat + 16, &kds);
    encode_gdt_entry(gdt_flat + 32, &ucs);
    encode_gdt_entry(gdt_flat + 40, &uds);
    encode_gdt_entry(gdt_flat + 48, &tss);

    load_gdt(gdt_flat);
}
