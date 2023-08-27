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

/* Max string buffer required when converting an int with value INT_MIN and base
 * 2 (calculated by length in bits + negative prefix + null terminator) */
#define ITOA_BUFSZ (sizeof(int) * CHAR_BIT) + 2

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

int printf(const char * restrict format, ...)
{
    int result = 0;

    va_list args;
    va_start(args, format);

    result = _vprintf(format, &args);

    va_end(args);

    return result;
}

int _vprintf(const char * restrict format, va_list * const args)
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
                value_arg = va_arg(*args, int);
                tty_put_char(value_arg);
                ++result;
            }
            /* string */
            else if (type == 's') {
                string_arg = va_arg(*args, char *);
                result += tty_write_string(string_arg);
            }
            /* int */
            else if (type == 'd' || type == 'i') {
                value_arg = va_arg(*args, int);
                if (value_arg < 0) {
                    value_arg = -value_arg;
                    tty_put_char('-');
                }
                itoa(output_buffer, value_arg, 10);
                result += tty_write_string(output_buffer);
            }
            /* octal */
            else if (type == 'o') {
                value_arg = va_arg(*args, unsigned int);
                itoa(output_buffer, value_arg, 8);
                result += tty_write_string(output_buffer);
            }
            /* hex */
            else if (type == 'x') {
                value_arg = va_arg(*args, unsigned int);
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
