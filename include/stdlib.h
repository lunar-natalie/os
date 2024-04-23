// Copyright (c) 2024 Natalie Wiggins. All rights reserved.
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <stddef.h>

// Kernel call stubs
void *malloc(size_t size);
void free(void *ptr);