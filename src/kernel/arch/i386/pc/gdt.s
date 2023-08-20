/*
 * gdt.s
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

.section .text
.global load_gdt
.type load_gdt, @function
load_gdt:
	movw	-2(%ebp), %ax
	movw	%ax, gdtr		/* Size */
	movl	-6(%ebp), %eax
	movl	%eax, gdtr + 2		/* Offset */
	lgdt	gdtr
	ret

gdtr:
.word 0         /* Size */
.long 0         /* Offset */
