/*
 * tss.s
 *
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

.section .text
.global load_tss
.type load_tss, @function
load_tss:
	push	%ebp			/* Save stack frame */
	mov	%esp, %ebp

	/* nth 8-byte descriptor in the GDT, symbolically OR-ed with with the
	 * RPL. */
	mov	12(%ebp), %ax		/* GDT index */
	mulw	8			/* Descriptor size */
	or	%ax, 8(%ebp)		/* RPL */
        ltr	%ax			/* Load selector into task register */

	pop	%ebp			/* Restore stack frame */
        ret
