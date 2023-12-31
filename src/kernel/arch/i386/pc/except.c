/*
 * except.c
 *
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/arch/i386/pc/except.h>

#include <kernel/runtime.h>

void __attribute__((noreturn)) exception_handler(void)
{
    kernel_exit();
}
