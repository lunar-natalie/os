/*
 * idt.c
 *
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/idt.h>
#include <kernel/arch/i386/pc/isr.h>

#include <stdint.h>

#include <kernel/error.h>

static idt_data_t  idt[IDT_LENGTH];
static idt_entry_t idt_entries[IDT_LENGTH];

void idt_init(void)
{
    /* Encode (skip null descriptor) */
    for (idt_index_t i = 0; i < IDT_LENGTH; ++i) {
        encode_idt_entry(&idt[i], &idt_entries[i]);
    }

    /* Load into CPU */
    if (load_idt(idt, IDT_LENGTH) != 0) {
        kernel_error("Failed to load IDT\n");
    }
}

void encode_idt_entry(idt_data_t * dest, idt_entry_t const * source)
{
    /* Offset */
    dest->offset_low      = source->offset & 0xFFFF;       /* Bits 0-15 */
    dest->offset_high     = (source->offset >> 16) & 0x0F; /* Bits 16-19  */
    /* Segment selector */
    dest->selector        = source->selector;
    /* Type attributes */
    dest->type_attributes = source->type_attributes;
}
