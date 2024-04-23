// Virtual memory manager
// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>

// Unimplemented
void *kmalloc(size_t size);
void kfree(void *ptr);