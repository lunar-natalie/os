/**
 * @file idt.h
 * @brief Interrupt Descriptor Table.
 */

/*
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ARCH_I386_PC_IDT_H
#define _KERNEL_ARCH_I386_PC_IDT_H

#include <stdint.h>

#define IDT_LENGTH UINT8_MAX

typedef uint8_t idt_index_t;

/** @brief High level representation of an IDT descriptor. */
typedef struct idt_entry {
    /** Address of the ISR entry point. */
    uint32_t offset;
    /** Code segment selector which points to a valid entry in the GDT or LDT.
     */
    uint16_t selector;
    /** Type attributes byte. */
    uint8_t  type_attributes;
} idt_entry_t;

/** @brief Writable IDT entry data arranged in bit-fields. */
typedef struct idt_data {
    /** Offset bits 0-15. */
    unsigned int offset_low      : 16;
    /** Segment selector. */
    unsigned int selector        : 16;
    /** Only used in software; has no effect on hardware. */
    unsigned int reserved        : 8;
    /** Type attributes byte. */
    unsigned int type_attributes : 8;
    /** Offset bits 16-31. */
    unsigned int offset_high     : 16;
} __attribute__((packed)) idt_data_t;

/** @brief IDT entry type attribute bits. */
enum idt_type_attributes {
    /** Present bit. Must be set for any valid descriptor. */
    IDT_ATTRIB_P     = 0b10000000,
    /** Descriptor privilege level (ring 0-3). */
    IDT_ATTRIB_DPL_1 = 0b00100000,
    IDT_ATTRIB_DPL_2 = 0b01000000,
    IDT_ATTRIB_DPL_3 = 0b01100000,
    /** Gate types. */
    IDT_ATTRIB_GATE_TASK =
        0b00000101, /** Task gate: IDT offset is unused should be zero. */
    IDT_ATTRIB_GATE_INT16  = 0b00000110, /** 16-bit interrupt gate. */
    IDT_ATTRIB_GATE_TRAP16 = 0b00000111, /** 16-bit trap gate. */
    IDT_ATTRIB_GATE_INT32  = 0b00001110, /** 32-bit interrupt gate. */
    IDT_ATTRIB_GATE_TRAP32 = 0b00001111, /** 32-bit trap gate. */
};

/** @brief Complete IDT type attribute bytes. */
enum idt_types {
    IDT_TYPE_RING0_TASK   = IDT_ATTRIB_P | IDT_ATTRIB_GATE_TASK,
    IDT_TYPE_RING0_INT16  = IDT_ATTRIB_P | IDT_ATTRIB_GATE_INT16,
    IDT_TYPE_RING0_TRAP16 = IDT_ATTRIB_P | IDT_ATTRIB_GATE_TRAP16,
    IDT_TYPE_RING0_INT32  = IDT_ATTRIB_P | IDT_ATTRIB_GATE_INT32,
    IDT_TYPE_RING0_TRAP32 = IDT_ATTRIB_P | IDT_ATTRIB_GATE_TRAP32,
    IDT_TYPE_RING3_INT16 =
        IDT_ATTRIB_P | IDT_ATTRIB_DPL_3 | IDT_ATTRIB_GATE_INT16,
    IDT_TYPE_RING3_TRAP16 =
        IDT_ATTRIB_P | IDT_ATTRIB_DPL_3 | IDT_ATTRIB_GATE_TRAP16,
    IDT_TYPE_RING3_INT32 =
        IDT_ATTRIB_P | IDT_ATTRIB_DPL_3 | IDT_ATTRIB_GATE_INT32,
    IDT_TYPE_RING3_TRAP32 =
        IDT_ATTRIB_P | IDT_ATTRIB_DPL_3 | IDT_ATTRIB_GATE_TRAP32,
};

/**
 * @brief Encodes built-in IDT entries and loads the IDT.
 *
 * @note Must be called after the GDT/LDT has been loaded.
 */
void idt_init(void);

void encode_idt_entry(idt_data_t * dest, idt_entry_t const * source);

/**
 * @brief Loads the IDT into the IDTR register.
 *
 * @param offset 32-bit linear table start address.
 * @param size 16-bit length of the table in bytes.
 * @return 0 if valid IDT, or 1 if invalid.
 */
extern int load_idt(idt_data_t * offset, uint16_t size);

#endif /* _KERNEL_ARCH_I386_PC_IDT_H */
