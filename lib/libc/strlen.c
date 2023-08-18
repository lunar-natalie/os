/*
 * strlen.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stddef.h>
#include <string.h>

size_t strlen(const char * str)
{
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}
