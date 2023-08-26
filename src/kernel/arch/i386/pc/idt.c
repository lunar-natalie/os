/*
 * idt.c
 *
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/gdt.h>
#include <kernel/arch/i386/pc/idt.h>

#include <stdint.h>

#include <kernel/error.h>

static idt_data_t  idt[IDT_LENGTH] __attribute__((aligned(4)));
static idt_entry_t idt_entries[IDT_LENGTH];

extern uint32_t isr_stub_table[IDT_LENGTH];

void idt_init(void)
{
    /* Add exception ISRs */
    for (uint8_t i = 0; i < 32; ++i) {
        idt_entries[i].offset          = isr_stub_table[i];
        idt_entries[i].selector        = GDT_INDEX_RING0_CODE;
        idt_entries[i].type_attributes = IDT_TYPE_RING0_INT32;
    }
    /* Encode */
    for (idt_index_t i = 0; i < 32; ++i) {
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
    dest->offset_low      = source->offset & 0xFFFF; /* Bits 0-15 */
    dest->offset_high     = source->offset >> 16;    /* Bits 16-31  */
    /* Segment selector */
    dest->selector        = source->selector;
    /* Type attributes */
    dest->type_attributes = source->type_attributes;
}
