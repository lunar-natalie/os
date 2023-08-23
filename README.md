Operating system.

# Supported platforms

- `ix86-pc-none-elf` (i386, i486, i586)

# Build

## Requirements

- CMake >= 3.25.1
- CMake backend
- GCC cross-compiler >= 8.1.0
- Binutils cross-toolchain

### Optional

- clang-format >= 14.0.6
- clang-tidy (requires Ninja or Makefile CMake backend)

### Tests

- grub-file (GRUB2)

### Bootable image creation

- grub-mkrescue (GRUB2)
- xorriso
- mtools

## CMake: Configure

Replace:

- `<TARGET_TRIPLET>` with the target platform `<MACH>-<VENDOR>-<SYS>-<ENV>`
- `<BUILD_TYPE>` with the desired build type (`Debug` or `Release`)

Additional options:

- `-Dos_ENABLE_TESTS=ON` - enable tests
- `-Dos_ENABLE_IMAGE=ON` - enable bootable image creation

```sh
cmake -DCMAKE_BUILD_TYPE:STRING=<BUILD_TYPE> -Dos_TARGET_TRIPLET=<TARGET_TRIPLET> -Bbuild
```

## CMake: Build

```sh
cmake --build build
```

# Testing the bootable image

## Requirements

- QEMU executable for the target architecture
- GRUB2 PC/BIOS modules

## Command line

Replace:

- `<ARCH>` with the target architecture (i386 for the x86 machine)

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
