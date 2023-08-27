/**
 * @file gdt.h
 * @brief Global Descriptor Table.
 */

/*
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ARCH_I386_PC_GDT_H
#define _KERNEL_ARCH_I386_PC_GDT_H

#include <stdint.h>

#include <kernel/arch/i386/pc/tss.h>

/** Number of entries in the GDT. */
#define GDT_LENGTH    6
/** Maximum memory access limit for a GDT segment descriptor. */
#define GDT_MAX_LIMIT 0xFFFFF

/** @brief Index of each selector in the GDT. */
enum gdt_index {
    GDT_INDEX_NULL       = 0,
    GDT_INDEX_RING0_CODE = 1,
    GDT_INDEX_RING0_DATA = 2,
    GDT_INDEX_RING3_CODE = 3,
    GDT_INDEX_RING3_DATA = 4,
    GDT_INDEX_RING0_TSS  = 5
};

typedef uint16_t gdt_offset_t;

/** @brief High-level representation of a GDT segment descriptor. */
typedef struct gdt_entry {
    /** Linear 32-bit address to the start of the segment. */
    uint32_t base;
    /** Maximum 20-bit unit addressable by the segment. */
    uint32_t limit;
    /** Access byte. */
    uint8_t  access;
    /** Flags byte. */
    uint8_t  flags;
} gdt_entry_t;

/** @brief Writable GDT entry data arranged in bit-fields. */
typedef struct gdt_data {
    /** Limit bits 0-15. */
    unsigned int limit_low  : 16;
    /** Base bits 0-15. */
    unsigned int base_low   : 24;
    /** Access byte. */
    unsigned int access     : 8;
    /** Limit bits 16-19.  */
    unsigned int limit_high : 4;
    /** Only used in software; has no effect on hardware. */
    unsigned int reserved   : 1;
    /** Flag byte. */
    unsigned int flags      : 3;
    /** Base bits 24-31. */
    unsigned int base_high  : 8;
} __attribute__((packed)) gdt_data_t;

/** @brief GDT entry access bits. */
enum gdt_access_bits {
    /** Present bit. Must be set for any valid segment. */
    GDT_ACCESS_P     = 0b10000000,
    /** Descriptor privilege level (ring 0-3). */
    GDT_ACCESS_DPL_1 = 0b00100000,
    GDT_ACCESS_DPL_2 = 0b01000000,
    GDT_ACCESS_DPL_3 = 0b01100000,
    /**
     * Descriptor type bit. Clear if system segment, set if code or data
     * segment.
     */
    GDT_ACCESS_S     = 0b00010000,
    /** Executable bit. */
    GDT_ACCESS_E     = 0b00001000,
    /**
     * Direction/conforming bit.
     *
     * Direction bit for data selectors: if clear, the segment grows up; if set,
     * the segment grows down.
     *
     * Conforming bit for code selectors: if clear, the segment can only be
     * executed from the ring set in the DPL; if set, the segment can be
     * executed from any privilege level.
     */
    GDT_ACCESS_DC    = 0b00000100,
    /**
     * Read-write bit. If clear, the segment is readable (code); if set, the
     * segment is writable (data).
     */
    GDT_ACCESS_RW    = 0b00000010,
    /** Accessed bit (set by CPU) */
    GDT_ACCESS_A     = 0b00000001
};

/** @brief GDT entry flag bits. */
enum gdt_flag_bits {
    /**
     * Granularity flag (scales segment limit). If clear, the limit is scaled in
     * 1 byte blocks; if set, the limit is scaled in 4K blocks.
     */
    GDT_FLAG_G  = 0b00001000,
    /**
     * Size flag. If clear, the descriptor defines a 16-bit protected mode
     * segment; if set, the descriptor defines a 32-bit protected mode segment.
     */
    GDT_FLAG_DB = 0b00000100,
    /**
     * Long-mode code flag. If set, the descriptor defines a 64-bit code
     * segment; for all other segment types the flag should be clear.
     */
    GDT_FLAG_L  = 0b00000010,
};

/**
 * @brief Encodes built-in GDT entries and loads the GDT.
 *
 * @param ring0_tss Pointer to the kernel-mode TSS structure.
 */
void gdt_init(tss_t const * ring0_tss);

/**
 * @brief Encodes a GDT entry from high-level descriptor information to a packed
 * data structure interpretable by the processor.
 *
 * @param dest Output pointer.
 * @param source Pointer to descriptor info.
 */
void encode_gdt_entry(gdt_data_t * dest, gdt_entry_t const * source);

/**
 * @brief Loads the GDT into the GDTR register.
 *
 * @param base 32-bit table start address.
 * @param limit 16-bit length of the table in bytes, subtracted by 1. The
 * maximum GDT size is 65536, whilst the maximum 16-bit value is 65535, hence
 * the need for the subtraction.
 * @return 0 if valid GDT, or 1 if invalid.
 */
extern int load_gdt(gdt_data_t * base, uint16_t limit);

#endif /* _KERNEL_ARCH_I386_PC_GDT_H */
