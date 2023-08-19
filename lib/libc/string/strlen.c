/*
 * strlen.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <string.h>

#include <stddef.h>

size_t strlen(const char * str)
{
    size_t len = 0;
    while (str[len]) {
        ++len;
    }
    return len;
}
