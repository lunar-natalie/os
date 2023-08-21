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
	mov	-2(%ebp), %ax
	mov	%ax, gdtr		/* Size (invalid if 0) */
	cmp	$0, %ax
	je	1f
	mov	-6(%ebp), %eax
	mov	%eax, gdtr + 2		/* Offset */
	lgdt	gdtr
	xor	%eax, %eax
	ret
1:	mov	$1, %eax
	ret

gdtr:
.word 0         /* Size */
.long 0         /* Offset */
