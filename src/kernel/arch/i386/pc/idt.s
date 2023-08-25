/*
 * idt.s
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

.section .text
.global load_idt
.type load_idt, @function
load_idt:
	push	%ebp			/* Save stack frame */
	mov	%esp, %ebp

	xor	%eax, %eax
	mov	12(%ebp), %ax		/* Size */
	mov	%ax, idtr

	cmp	$0, %ax			/* (invalid if 0) */
	je	1f

	mov	8(%ebp), %eax		/* Offset */
	mov	%eax, idtr + 2
	lidt	idtr

	xor	%eax, %eax
	jmp	2f

1:	mov	$1, %eax

2:	pop	%ebp			/* Restore stack frame */
	ret

idtr:
.word 0         /* Size */
.long 0         /* Offset */
