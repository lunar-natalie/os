/*
 * idt.h
 * Interrupt Descriptor Table.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ARCH_I386_PC_IDT_H
#define _KERNEL_ARCH_I386_PC_IDT_H

#include <stdint.h>

/* High level representation of an IDT descriptor. */
struct idt_entry {
    /* Address of the ISR entry point. */
    uint32_t offset;
    /* Code segment selector which points to a valid entry in the GDT or LDT. */
    uint16_t selector;
    /* Type attributes byte. */
    uint8_t  type_attributes;
};

typedef struct idt_entry idt_entry_t;

/* Writable IDT entry data arranged in bit-fields. */
struct idt_data {
    /* Offset bits 0-15. */
    unsigned int offset_low      : 16;
    /* Segment selector. */
    unsigned int selector        : 16;
    /* Only used in software; has no effect on hardware. */
    unsigned int reserved        : 1;
    /* Type attirubtes byte. */
    unsigned int type_attributes : 8;
    /* Offset bits 16-31. */
    unsigned int offset_high     : 16;
} __attribute__((packed));

typedef struct idt_data idt_data_t;

/* IDT entry type attribute bits. */
enum idt_type_attributes {
    /* Present bit. Must be set for any valid descriptor. */
    IDT_ATTRIB_P     = 0b10000000,
    /* Descriptor privellege level (ring 0-3). */
    IDT_ATTRIB_DPL_1 = 0b00100000,
    IDT_ATTRIB_DPL_2 = 0b01000000,
    IDT_ATTRIB_DPL_3 = 0b01100000,
    /* Gate types. */
    IDT_ATTRIB_GATE_TYPE_TASK =
        0b00000101, /* Task gate: IDT offset is unused should be zero. */
    IDT_ATTRIB_GATE_TYPE_INT16  = 0b00000110, /* 16-bit interrupt gate. */
    IDT_ATTRIB_GATE_TYPE_TRAP16 = 0b00000111, /* 16-bit trap gate. */
    IDT_ATTRIB_GATE_TYPE_INT32  = 0b00001110, /* 32-bit interrupt gate. */
    IDT_ATTRIB_GATE_TYPE_TRAP32 = 0b00001111, /* 32-bit trap gate. */
};

#endif /* _KERNEL_ARCH_I386_PC_IDT_H */
