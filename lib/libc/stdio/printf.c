/*
 * printf.c
 *
 * OS libk
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>

#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

/* Max string buffer required for itoa when converting from an int with value
 * INT_MIN and base 2 (calculated by length in bits + negative prefix + null
 * terminator). */
#define ITOA_BUFSZ (sizeof(int) * CHAR_BIT) + 2

/**
 * @brief Converts an integer to an ASCII string (implementation-defined).
 *
 * Converts an integer value to a null-terminated string using the specified
 * base and stores the result in the array given by the `str` parameter.
 *
 * If `base` is 10 and `value` is negative, the resulting string is preceded
 * with a minus sign (-). With any other base, `value` is always considered
 * unsigned.
 *
 * `str` should be an array long enough to contain any possible value
 * (ITOA_BUFSZ).
 *
 * @param value Value to be converted to a string.
 * @param str Array in memory where to store the resulting null-terminated
 * string.
 * @param base Numerical base used to represent the value as a string, between 2
 * and 36, where 10 means decimal base, 16 hexadecimal, 8 octal, and 2 binary.
 *
 * @return A pointer to the resulting null-terminated string, same as parameter
 * `str`.
 */
char * itoa(char * dest, int value, int base);

int printf(const char * restrict format, ...)
{
    int     result = 0;
    va_list args;
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);

    return result;
}

int vprintf(const char * restrict format, va_list vlist) // NOLINT
{
    int    result = 0;
    int    value_arg;
    char * string_arg;
    char   output_buffer[ITOA_BUFSZ];
    while (*format != '\0') {
        if (*format == '%') {
            char type = *++format;
            /* char */
            if (type == 'c') {
                value_arg = va_arg(vlist, int);
                tty_put_char(value_arg);
                ++result;
            }
            /* string */
            else if (type == 's') {
                string_arg = va_arg(vlist, char *);
                result += tty_write_string(string_arg);
            }
            /* int */
            else if (type == 'd' || type == 'i') {
                value_arg = va_arg(vlist, int);
                if (value_arg < 0) {
                    value_arg = -value_arg;
                    tty_put_char('-');
                }
                itoa(output_buffer, value_arg, 10);
                result += tty_write_string(output_buffer);
            }
            /* octal */
            else if (type == 'o') {
                value_arg = va_arg(vlist, unsigned int);
                itoa(output_buffer, value_arg, 8);
                result += tty_write_string(output_buffer);
            }
            /* hex */
            else if (type == 'x') {
                value_arg = va_arg(vlist, unsigned int);
                itoa(output_buffer, value_arg, 16);
                result += tty_write_string(output_buffer);
            }
        }
        else {
            tty_put_char(*format);
            ++result;
        }
        ++format;
    }
    return result;
}

char * itoa(char * dest, int value, int base)
{
    char              buffer[ITOA_BUFSZ];
    static const char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (base < 2 || base > 36) {
        /* Invalid base */
        return NULL;
    }

    /* Write from end of buffer */
    char * ptr = &buffer[sizeof(buffer) - 1];
    *ptr       = '\0';

    /* Signed value */
    int value_n = value < 0 ? value : -value;

    /* Write digits */
    do {
        /* Get next unit */
        *(--ptr) = digits[-(value_n % base)];
        value_n /= base;
    } while (value_n);

    /* Prefix if signed */
    if (value_n < 0) {
        *(--ptr) = '-';
    }

    /* Strip leading nulls and return a copy of the string from the starting
     * character */
    size_t size_used = &buffer[sizeof(buffer)] - ptr;
    return memcpy(dest, ptr, size_used);
}
