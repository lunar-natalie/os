/**
 * @file string.h
 * @brief String utilities.
 */

/*
 * OS libk
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

/**
 * @brief Returns the length of the given byte string, that is, the number of
 * characters in a character array whose first element is pointed to by str up
 * to and not including the first null character.
 *
 * @details The behavior is undefined if there is no null character in the
 * character array pointed to by `str`.
 *
 * @param str Pointer to the null-terminated byte string to be examined.
 *
 * @return The length of the null-terminated string `str`.
 */
size_t strlen(const char * str);

/**
 * @brief Copies the value `(unsigned char)ch` into each of the first count
 * characters of the object pointed to by `dest`.
 *
 * @details The behavior is undefined if access occurs beyond the end of the
 * dest array. The behavior is undefined if dest is a null pointer.
 *
 * @param dest Pointer to the object to fill.
 * @param ch Fill byte.
 * @param count Number of bytes to fill.
 *
 * @return A copy of `dest`.
 */
void * memset(void * dest, int ch, size_t count);

/**
 * @brief Copies `count` characters from the object pointed to by `src` to the
 * object pointed to by `dest`.
 *
 * @details Both objects are interpreted as arrays of `unsigned char`.
 *
 * @param dest Pointer to the object to copy to.
 * @param src Pointer to the object to copy from.
 * @param count Number of bytes to copy.
 *
 * @return A copy of `dest`.
 */
void * memcpy(void * restrict dest, const void * restrict src, size_t count);

#endif /* _STRING_H */
