<p align="center">
  <b>Operating System Project</b><br>
  <br>
  <a href="https://github.com/lunar-natalie/os/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/lunar-natalie/os"
      alt="License">
  </a>
  <a href="https://github.com/lunar-natalie/os/actions/workflows/build.yml">
    <img src="https://github.com/lunar-natalie/os/actions/workflows/build.yml/badge.svg?event=push"
      alt="Build">
  </a>
  <a href="https://github.com/lunar-natalie/os/actions/workflows/docs.yml">
    <img src="https://github.com/lunar-natalie/os/actions/workflows/docs.yml/badge.svg?event=push"
      alt="Documentation">
  </a><br>
  <br>
  <a href="https://lunar-natalie.github.io/os">Docs</a> |
    <a href="https://github.com/lunar-natalie/os">GitHub</a><br>
  <br>
  <i>// Under Construction //</i><br>
  <br>
</p>

# Supported platforms

- `ix86-pc-none-elf` (i386, i486, i586, i686)

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

## Docker environment

A [Docker image](https://github.com/lunar-natalie/os-buildenv-i686-pc-none-elf) is provided with an included toolchain targeting `i686-pc-none-elf` for CI builds.

## CMake: Configure

Replace:

- `<BUILD_TYPE>` with the desired build type (`Debug` or `Release`)
- `<TARGET_TRIPLET>` with the target platform `<MACH>-<VENDOR>-<SYS>-<ENV>`

Additional options:

- `-Dos_ENABLE_TESTS:BOOL=ON` - Enable tests
- `-Dos_ENABLE_IMAGE:BOOL=ON` - Enable bootable image creation

```sh
cmake -DCMAKE_BUILD_TYPE:STRING=<BUILD_TYPE> -Dos_TARGET_TRIPLET:STRING=<TARGET_TRIPLET> -Bbuild
```

## CMake: Build

```sh
cmake --build build
```

# Testing the bootable image

## Requirements

- QEMU executable for the target architecture
- GRUB2 PC/BIOS modules (ix86-pc machine type)

## Command line

Replace:

- `<ARCH>` with the target architecture (i386 for ix86 machine type)

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
