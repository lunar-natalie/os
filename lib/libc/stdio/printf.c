/*
 * printf.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>

#include <stdarg.h>
#include <stdint.h>

#include <kernel/tty.h>

/* The maximum number of digits for an unsigned integer in base 2 is equal
 * to the number of bits of the unsigned integer type, and
 * therefore the same goes for every other base. */
#define UINT_BITS sizeof(unsigned int) * sizeof(unsigned int)

unsigned int
itoa(char * buffer, unsigned int length, unsigned int num, int base)
{
    static const char digits[] = "0123456789ABCDEF"; /* Representation digits */
    char *            ptr; /* Pointer to the current character in the buffer */

    /* Write null terminator */
    ptr  = &buffer[length - 1];
    *ptr = '\0';

    do {
        /* Set output char to the digit char indexed by the remainder of
         * dividing the digit by the base */
        *--ptr = digits[num % base];
        /* Divide by base to get to the next digit until we've got all the
         * digits */
        num /= base;
    } while (num != 0);

    return buffer - ptr; /* Number of digits written */
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
    char   type;
    int    value_arg;
    char * string_arg;
    char   output_buffer[UINT_BITS];

    while (*format != '\0') {
        if (*format == '%') {
            type = *++format;
            /* char */
            if (type == 'c') {
                value_arg = va_arg(*args, int);
                tty_put_char(value_arg);
                ++result;
            }
            /* int */
            else if (type == 'd' || type == 'i') {
                value_arg = va_arg(*args, int);
                if (value_arg < 0) {
                    value_arg = -value_arg;
                    tty_put_char('-');
                }
                itoa(output_buffer, UINT_BITS, value_arg, 10);
                result += tty_write_string(output_buffer);
            }
            /* octal */
            else if (type == 'o') {
                value_arg = va_arg(*args, unsigned int);
                itoa(output_buffer, UINT_BITS, value_arg, 8);
                result += tty_write_string(output_buffer);
            }
            /* string */
            else if (type == 's') {
                string_arg = va_arg(*args, char *);
                result += tty_write_string(string_arg);
            }
            /* hex */
            else if (type == 'x') {
                value_arg = va_arg(*args, unsigned int);
                itoa(output_buffer, UINT_BITS, value_arg, 16);
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
