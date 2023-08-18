/*
 * strlen.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stddef.h>
#include <string.h>

size_t strlen(const char * s)
{
    size_t len = 0;
    while (s[len]) {
        len++;
    }
    return len;
}
