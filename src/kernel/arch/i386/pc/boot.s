/*
 * boot.s
 * Multiboot v1-compliant kernel bootstrap assembly for i386-pc.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

/* Multiboot constants */
.set ALIGN,	1 << 0			/* Align loaded modules on page boundaries */
.set MEMINFO,	1 << 1			/* Provide memory map */
.set FLAGS,	ALIGN | MEMINFO		/* 'flag' field */
.set MAGIC,	0x1BADB002		/* Kernel identifier */
.set CHECKSUM,	-(MAGIC + FLAGS)

/* Multiboot header, placed in the first 8K of the kernel binary. */
.section .multiboot
.align 4				/* Align to 32-bit page boundary */
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Top-down 16K stack.
 * Aligned to 16 bits in the System V ABI. */
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

/* Entry point */
.section .text
.global _start
.type _start, @function
_start:
	/* Loaded in 32-bit protected mode.
	 * Kernel now has full CPU control, no runtime utilities are implemented
	 * and GDT/paging is yet to be initialized. */

	/* Load stack pointer */
	mov     $stack_top, %esp

	/* Save stack segment and pointer for TSS */
	mov	%ss, _boot_ss0
	mov	%esp, _boot_esp0

	/* Enter high level C kernel.
	 *
	 * The stack must be 16-bit aligned at the time of this call using the
	 * System V ABI. This state is preserved as the stack is initially empty
	 * and 16-bit aligned. */
	call    kernel_main

/* Set _start symbol size for debugging/call tracing */
.size _start, . - _start

_end:
	/* Stop execution */
	cli
1:	hlt				/* Halt on NMI */
	jmp     1b

.global kernel_exit
.type kernel_exit, @function
kernel_exit:
	jmp     _end

.global _boot_ss0
.global _boot_esp0
_boot_ss0:	.long 0
_boot_esp0:	.long 0
