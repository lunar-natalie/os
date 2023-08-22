Operating system

# Supported platforms

- i386-pc

# Build

## Requirements

- CMake >= 3.25.1
- CMake backend
- GCC cross-compiler >= 8.1.0
- Binutils (cross-target)

### Optional

- clang-format >= 14.0.6
- clang-tidy

### Bootable image creation

- grub-mkrescue
- xorriso
- mtools

## CMake: Configure

Replace:

- `<TARGET_TRIPLET>` with the target platform `<MACH>-<ARCH>-<VENDOR>`
- `<BUILD_TYPE>` with the desired build type (`Debug` or `Release`)

### Without bootable image

```sh
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -Dos_TARGET_TRIPLET=<TARGET_TRIPLET> -Dos_ENABLE_TESTS=ON -Bbuild
```

### With bootable image

```sh
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -Dos_TARGET_TRIPLET=<TARGET_TRIPLET> -Dos_ENABLE_TESTS=ON -Dos_ENABLE_IMAGE=ON -Bbuild
```

## CMake: Build

```sh
cmake --build build
```

# Testing the bootable image

Requires a QEMU executable with support for the target architecture.

Replace:

- `<ARCH>` with the target architecture

```sh
qemu-system-<ARCH> -cdrom build/os.iso
```

# License

Copyright (c) 2023 Natalie Wiggins.

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
