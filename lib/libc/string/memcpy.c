/*
 * memcpy.c
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <string.h>

#include <stddef.h>

void * memcpy(void * dest, const void * src, size_t count)
{
    char *       cdest = (char *) dest;
    const char * csrc  = (char *) src;
    for (size_t i = 0; i < count; ++i) {
        cdest[i] = csrc[i];
    }
    return dest;
}
