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
	push	%ebp
	mov	%esp, %ebp		/* Set frame pointer */

	xor	%eax, %eax
	mov	12(%ebp), %ax		/* Limit */
	mov	%ax, gdtr

	cmp	$0, %ax			/* (invalid if 0) */
	je	1f

	mov	8(%ebp), %eax		/* Base */
	mov	%eax, gdtr + 2
	lgdt	gdtr

	xor	%eax, %eax
	jmp	2f

1:	mov	$1, %eax

2:	pop	%ebp			/* Restore stack frame */
	ret

gdtr:
.word 0         /* Limit */
.long 0         /* Base */
