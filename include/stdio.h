/**
 * @file stdio.h
 * @brief IO utilities.
 */

/*
 * OS libk
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>

/**
 * Loads the data from the given locations, converts them to character string
 * equivalents and writes the results to `stdout`.
 *
 * @param format Pointer to a null-terminated byte string specifying how to
 * interpret the data
 * @param ...	Arguments specifying data to print. If any argument after
 * default argument promotions is not the type expected by the corresponding
 * conversion specifier, or if there are fewer arguments than required by
 * format, the behavior is undefined. If there are more arguments than required
 * by format, the extraneous arguments are evaluated and ignored.
 *
 * @note Incomplete implementation.
 */
int printf(const char * restrict format, ...);

/**
 * Loads the data from the locations, defined by `vlist`, converts them to
 * character string equivalents and writes the results to `stdout`.
 *
 * @param format Pointer to a null-terminated character string specifying how to
 * interpret the data.
 * @param vlist Variable argument list containing the data to print.
 *
 * @note Incomplete implementation.
 */
int vprintf(const char * restrict format, va_list vlist);

#endif /* _STDIO_H */
