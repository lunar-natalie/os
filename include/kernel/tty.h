/*
 * tty.h
 * Terminal utilities.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_TTY_H_
#define _KERNEL_TTY_H_

void tty_init(void);
void tty_writestring(const char * s);

#endif // _KERNEL_TTY_H_
