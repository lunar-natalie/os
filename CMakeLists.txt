# Global CMake config.

cmake_minimum_required(VERSION 3.25.1)

project(os
  VERSION 1.0.0
  LANGUAGES C ASM-ATT)

# Options
set(os_TARGET_TRIPLET "" CACHE STRING "Target platform triplet (<MACH>-<VENDOR>-<SYS>-<ENV>). Defaults to the platform reported by the C compiler.")
option(os_ENABLE_BUILD "Enable build targets" ON)
option(os_ENABLE_TESTS "Enable tests" ON)
option(os_ENABLE_IMAGE "Enable bootable image build" ON)
option(os_ENABLE_CLANG_TIDY "Enable clang-tidy for processing source files" ON)
option(os_ENABLE_CLANG_FORMAT "Enable clang-format target" OFF)
option(os_ENABLE_DOCS "Enable documentation built target" OFF)
option(os_ENABLE_DOCS_AUX "Enable building of auxiliary documentation (markdown files)" ON)
option(os_ENABLE_STYLED_DOCS "Enable custom Doxygen stylesheet" ON)

# Tools
include(cmake/utils.cmake)
set(os_SOURCE_DIRNAMES
  "include"
  "lib"
  "src"
)
get_all_source_files()
if(os_ENABLE_BUILD AND os_ENABLE_CLANG_TIDY)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  include(cmake/ClangTidy.cmake)
endif()
if(os_ENABLE_CLANG_FORMAT)
  include(cmake/ClangFormat.cmake)
endif()

# Build targets
if(os_ENABLE_BUILD)
  # Set up platform environment
  set(CMAKE_C_STANDARD 17)
  set(CMAKE_C_STANDARD_REQUIRED True)
  set(CMAKE_C_EXTENSIONS Off)
  load_target_platform()

  # Tests
  if(os_ENABLE_TESTS)
    include(CTest)
    find_program(GRUB_FILE grub-file)
  else()
    message("-- Tests are disabled")
  endif()

  # Bootable image dependencies
  if(os_ENABLE_IMAGE)
    find_program(GRUB_MKRESCUE grub-mkrescue)
    if(GRUB_MKRESCUE STREQUAL "GRUB_MKRESCUE-NOTFOUND")
      set(os_ENABLE_IMAGE OFF)
      message("-- grub-mkrescue not found: image build has been disabled")
    endif()
    else()
    message("-- Image build is disabled")
  endif()

  # Add source directories
  add_subdirectory(include)
  add_subdirectory(lib)
  add_subdirectory(src)

  # Add image target
  if(os_ENABLE_IMAGE)
    add_subdirectory(image)
  endif()
else()
  message("-- Build is disabled")
endif()

# Docs
if(os_ENABLE_DOCS)
  find_package(Doxygen)
  if(NOT DOXYGEN_FOUND)
    set(os_ENABLE_DOCS OFF)
    message(WARNING "Unable to find Doxygen")
    message("-- Documentation build is disabled")
  endif()

  add_subdirectory(docs)
else()
  message("-- Documentation build is disabled")
endif()
