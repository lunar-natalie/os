/*
 * error.h
 * Kernel error handling.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ERROR_H
#define _KERNEL_ERROR_H

void kernel_error(const char * restrict format, ...);

#endif /* _KERNEL_ERROR_H */
