/**
 * @file runtime.h
 * @brief Kernel runtime utilities.
 */

/*
 * OS Kernel
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef _KERNEL_RUNTIME_H
#define _KERNEL_RUNTIME_H

/** Immediately terminates the main C kernel thread. */
extern void kernel_exit(void);

#endif /* _KERNEL_RUNTIME_H */
