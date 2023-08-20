/*
 * stdio.h
 * IO utilities.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>

int printf(const char * restrict format, ...);

int _vprintf(const char * restrict format, va_list * const args);

#endif /* _STDIO_H */
