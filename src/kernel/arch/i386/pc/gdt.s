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
        add     $4, %esp
        movw    (%esp), %ax
        add     $4, %esp
        movl    (%esp), %eax
        add     $4, %esp
        addl    (%esp), %eax
        lgdt    (gdtr)
        sub     $12, %esp
        ret

gdtr:
.word 0         /* Limit */
.long 0         /* Base */
