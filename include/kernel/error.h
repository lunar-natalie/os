/**
 * @file error.h
 * @brief Kernel error handling.
 */

/*
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_ERROR_H
#define _KERNEL_ERROR_H

/**
 * @brief Sends the output to the terminal buffer and terminates the kernel.
 *
 * @param format Pointer to a null-terminated byte string specifying how to
 * interpret the data. `printf` format specifiers are supported.
 * @param ...  Arguments specifying data to print.
 *
 * @see printf
 */
void kernel_error(const char * restrict format, ...);

#endif /* _KERNEL_ERROR_H */
