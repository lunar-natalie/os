/*
 * tty.h
 * Terminal utilities.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void tty_init(void);

void tty_put_char(char c);

size_t tty_write_string(const char * s);

#endif /* _KERNEL_TTY_H */
