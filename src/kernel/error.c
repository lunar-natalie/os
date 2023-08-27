/*
 * error.c
 *
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <kernel/error.h>
#include <kernel/runtime.h>

#include <stdio.h>

void kernel_error(const char * restrict format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    kernel_exit();
}
