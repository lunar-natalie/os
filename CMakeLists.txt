# Global CMake config.

cmake_minimum_required(VERSION 3.25.1)

project(os
  VERSION 1.0.0
  LANGUAGES C ASM-ATT)

# Options
set(os_TARGET_TRIPLET "" CACHE STRING "Target platform triplet. Defaults to the platform reported by the C compiler.")
option(os_ENABLE_TESTS "Enable unit tests" ON)
option(os_ENABLE_IMAGE "Enable bootable image build" ON)
option(os_ENABLE_CLANG_TIDY "Enable clang-tidy for processing source files" ON)

# Tools
include(cmake/utils.cmake)

set(os_SOURCE_DIRNAMES
  "include"
  "lib"
  "src"
)

get_all_source_files()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/ClangFormat.cmake)
if(os_ENABLE_CLANG_TIDY)
  include(cmake/ClangTidy.cmake)
endif()

# Tests
if(os_ENABLE_TESTS)
  include(CTest)
  find_program(GRUB_FILE grub-file)
  message("-- Enabled unit tests")
else()
  message("-- Unit tests are disabled")
endif()

# Bootable image
if(os_ENABLE_IMAGE)
  find_program(GRUB_MKRESCUE grub-mkrescue)
  if(GRUB_MKRESCUE STREQUAL "GRUB_MKRESCUE-NOTFOUND")
    set(os_ENABLE_IMAGE OFF)
    message("-- grub-mkrescue not found: image build has been disabled")
  else()
    message("-- Enabled image build")
  endif()
else()
  message("-- Image build is disabled")
endif()

# Set up platform environment
set(CMAKE_C_STANDARD 17)
load_target_platform()

# Add source directories
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)

if(os_ENABLE_IMAGE)
  add_subdirectory(image)
endif()
