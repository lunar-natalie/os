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

char * print_base(unsigned int num, int base)
{
    static char digits[] = "0123456789ABCDEF";
    static char buffer[UINT32_MAX];
    char *      ptr;

    ptr  = &buffer[UINT32_MAX - 1];
    *ptr = '\0';

    do {
        *--ptr = digits[num % base];
        num /= base;
    } while (num != 0);

    return ptr;
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
    int result = 0;

    char   type;
    int    value_arg;
    char * string_arg;

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
                result += tty_write_string(print_base(value_arg, 10));
            }
            /* octal */
            else if (type == 'o') {
                value_arg = va_arg(*args, unsigned int);
                result += tty_write_string(print_base(value_arg, 8));
            }
            /* string */
            else if (type == 's') {
                string_arg = va_arg(*args, char *);
                result += tty_write_string(string_arg);
            }
            /* hex */
            else if (type == 'x') {
                value_arg = va_arg(*args, unsigned int);
                result += tty_write_string(print_base(value_arg, 16));
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
