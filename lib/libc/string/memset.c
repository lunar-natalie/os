/*
 * memset.c
 *
 * OS libk
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <string.h>

#include <stddef.h>

void * memset(void * dest, int ch, size_t count)
{
    int * idest = (int *) dest;
    for (size_t i = 0; i < count; ++i) {
        idest[i] = ch;
    }
    return dest;
}
