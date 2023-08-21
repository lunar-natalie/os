/*
 * tss.s
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

.section .text
.global flush_tss
.type flush_tss, @function
flush_tss:
	/* Fifth 8-byte selector, symbolically OR-ed with 0 to set the RPL
	 * (requested privilege level) */
        mov	$((5 * 8) | 0), %ax
        ltr	%ax			/* Load selector into task register */
        ret
