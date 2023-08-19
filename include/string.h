/*
 * string.h
 * String utilities.
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

size_t strlen(const char * str);

void * memcpy(void * dest, const void * src, size_t count);

#endif // _STRING_H
