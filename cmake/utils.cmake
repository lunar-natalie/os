# utils.cmake
# CMake utility definitions.
#
# Requires CMake 3.25.1.
#
# Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

# Loads platform-dependent variables using the target platform triplet.
#
# Sets ${PROJECT_NAME}_TARGET_TRIPLET using the compiler, if unset.
#
# Sets ${PROJECT_NAME}_TARGET_<PROP>, where <PROP> is a triplet property
# (MACH, ARCH, VENDOR, SYS, ENV).
#
# Sets ${PROJECT_NAME}_TARGET_PREFIX (<MACH>-<ENV>).
#
# Ensures the correct toolchain components are used for the target platform.
#
# Throws a fatal error if the platform is invalid or cannot be properly
# inferred by the build system.
macro(load_target_platform)
  # Get triplet from compiler if not set
  if(${PROJECT_NAME}_TARGET_TRIPLET STREQUAL "")
    execute_process(
      COMMAND ${CMAKE_C_COMPILER} -dumpmachine
      OUTPUT_VARIABLE ${PROJECT_NAME}_TARGET_TRIPLET)

    # Use only provided toolchain components to target host platform
    set(HOST_TOOLCHAIN ON)
  else()
    # Triplet set, use platform-specific build toolchain components
    set(HOST_TOOLCHAIN OFF)
  endif()

  if(${PROJECT_NAME}_TARGET_TRIPLET STREQUAL "")
    message(FATAL_ERROR "Failed to obtain target platform information from the compiler.")
  endif()

  message("-- Configuring build for target platform: ${${PROJECT_NAME}_TARGET_TRIPLET}")

  # Split triplet into arch, vendor, sys
  string(REPLACE "-" ";" TRIPLET_LIST ${${PROJECT_NAME}_TARGET_TRIPLET})
  list(LENGTH TRIPLET_LIST TRIPLET_LENGTH)
  if(${TRIPLET_LENGTH} LESS 3)
    message(FATAL_ERROR "Invalid target platform triplet.")
  endif()
  list(GET TRIPLET_LIST 0 ${PROJECT_NAME}_TARGET_MACH)
  list(GET TRIPLET_LIST 1 ${PROJECT_NAME}_TARGET_VENDOR)
  list(GET TRIPLET_LIST 2 ${PROJECT_NAME}_TARGET_SYS)
  list(GET TRIPLET_LIST 3 ${PROJECT_NAME}_TARGET_ENV)

  if(${PROJECT_NAME}_TARGET_MACH STREQUAL "")
    message(FATAL_ERROR "Invalid target machine.")
  endif()
  if(${PROJECT_NAME}_TARGET_VENDOR STREQUAL "")
    message(FATAL_ERROR "Invalid target vendor.")
  endif()
  if(${PROJECT_NAME}_TARGET_SYS STREQUAL "")
    message(FATAL_ERROR "Invalid target system.")
  endif()
  if(${PROJECT_NAME}_TARGET_ENV STREQUAL "")
    message(FATAL_ERROR "Invalid target environment.")
  endif()

  # Use i386 arch if x86 machine
  set(X86 "")
  string(REGEX MATCH "i[0-9]86" X86 "${${PROJECT_NAME}_TARGET_MACH}")
  if(X86 STREQUAL "")
    set(${PROJECT_NAME}_TARGET_ARCH "${PROJECT_NAME}_TARGET_MACH")
  else()
    set(${PROJECT_NAME}_TARGET_ARCH "i386")
  endif()

  message("-- Building for machine: ${${PROJECT_NAME}_TARGET_MACH}")
  message("-- Building for architecture: ${${PROJECT_NAME}_TARGET_ARCH}")

  # Load platform-specific build toolchain components
  if(HOST_TOOLCHAIN)
    set(${PROJECT_NAME}_TARGET_TOOLCHAIN_PREFIX "")
  else()
    set(${PROJECT_NAME}_TARGET_TOOLCHAIN_PREFIX
      "${${PROJECT_NAME}_TARGET_MACH}-${${PROJECT_NAME}_TARGET_ENV}")

    # Check if Clang is available for cross-compilation
    if(NOT(CMAKE_C_COMPILER_ID STREQUAL "Clang"))
      # Clang unavailable, find (G)CC
      find_program(CMAKE_C_COMPILER
        NAMES
          ${${PROJECT_NAME}_TARGET_TOOLCHAIN_PREFIX}-cc
          ${${PROJECT_NAME}_TARGET_TOOLCHAIN_PREFIX}-gcc
        REQUIRED)
      message("-- Using C cross-compiler: ${CMAKE_C_COMPILER}")
    else()
      # Add target platform to compile options
      add_compile_options(
        $<$<COMPILE_LANGUAGE:C>:--target=${${PROJECT_NAME}_TARGET_TRIPLET}>)
    endif()

    # Find AS
    find_program(ASM_ATT_COMPILER
      ${${PROJECT_NAME}_TARGET_TOOLCHAIN_PREFIX}-as
      REQUIRED)
    set(CMAKE_ASM-ATT_COMPILER ${ASM_ATT_COMPILER})
    message("-- Using assembler: ${CMAKE_ASM-ATT_COMPILER}")
  endif()

  # Find LD
  find_program(${PROJECT_NAME}_LINKER
    NAMES
      ${${PROJECT_NAME}_TARGET_TOOLCHAIN_PREFIX}-ld
      ${${PROJECT_NAME}_TARGET_TOOLCHAIN_PREFIX}-ld.lld
    REQUIRED)
  message("-- Using linker: ${${PROJECT_NAME}_LINKER}")
  set(CMAKE_C_LINK_EXECUTABLE
    "${${PROJECT_NAME}_LINKER} <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
endmacro()

# Calls `add_subdirectory` to load platform-specific sources for the current
# architecture and vendor from the current source directory
# (<CURRENT_SOURCE_DIR>/arch/<ARCH>/<VENDOR>).
macro(add_platform_subdirectory)
  add_subdirectory(
"${CMAKE_CURRENT_SOURCE_DIR}/\
arch/\
${${PROJECT_NAME}_TARGET_ARCH}/\
${${PROJECT_NAME}_TARGET_VENDOR}"
  )
endmacro()

# Updates an existing target.
#
#   update_parent(
#     TARGET <TARGET>
#     SOURCES <SOURCE> ...
#     COMPILE_OPTIONS <OPTION> ...
#     LINKER_SCRIPT <FILE> )
#
# TARGET - Desired target to modify, parenting the current source directory.
# SOURCES [optional] - List of source files to add.
# COMPILE_OPTIONS [optional] - List of extra options to pass to the compiler for
#   the whole target.
# LINKER_SCRIPT [optional] - Path to the script to use when linking the target.
#
# File paths are processed relative to the current source directory.
macro(update_parent)
  set(ONE_VALUE_ARGS TARGET LINKER_SCRIPT)
  set(MULTI_VALUE_ARGS SOURCES COMPILE_OPTIONS)
  cmake_parse_arguments("update_parent"
    "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}"
    ${ARGN})

  # Add sources
  if(NOT("${update_parent_SOURCES}" STREQUAL ""))
    get_absolute_paths(
      RELATIVE_PATHS ${update_parent_SOURCES}
      OUTPUT_VARIABLE SOURCES_ABSOLUTE)
    set_property(TARGET ${update_parent_TARGET}
      APPEND PROPERTY SOURCES ${SOURCES_ABSOLUTE})
  endif()

  # Add compile options
  if(NOT("${update_parent_COMPILE_OPTIONS}") STREQUAL "")
    set_property(TARGET ${update_parent_TARGET}
      APPEND PROPERTY COMPILE_OPTIONS "${update_parent_COMPILE_OPTIONS}")
  endif()

  # Set linker script
  if(NOT("${update_parent_LINKER_SCRIPT}") STREQUAL "")
    set_property(TARGET ${update_parent_TARGET}
      APPEND PROPERTY LINK_OPTIONS
        -T${CMAKE_CURRENT_SOURCE_DIR}/${update_parent_LINKER_SCRIPT})
    set_property(TARGET ${update_parent_TARGET}
      APPEND PROPERTY LINK_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/${update_parent_LINKER_SCRIPT})
  endif()
endmacro()

# Generates a list of absolute paths.
#
#   get_absolute_paths(
#     RELATIVE_PATHS <PATH> ...
#     OUTPUT_VARIABLE <VAR> )
#
# RELATIVE_PATHS - Paths relative to ${CMAKE_CURRENT_SOURCE_DIR}.
# OUTPUT_VARIABLE - Name of variable in which absolute paths will be stored.
macro(get_absolute_paths)
  set(ONE_VALUE_ARGS OUTPUT_VARIABLE)
  set(MULTI_VALUE_ARGS RELATIVE_PATHS)
  cmake_parse_arguments("get_absolute_paths"
    "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}"
    ${ARGN})

  foreach(PATH ${get_absolute_paths_RELATIVE_PATHS})
    list(APPEND ${get_absolute_paths_OUTPUT_VARIABLE}
      "${CMAKE_CURRENT_SOURCE_DIR}/${PATH}")
  endforeach()
endmacro()

# Sets ${PROJECT_NAME}_ALL_SOURCE_FILES by globbing for source files in
# ${${PROJECT_NAME}_SOURCE_DIRNAMES}.
macro(get_all_source_files)
  set(${PROJECT_NAME}_ALL_SOURCE_FILES)
  foreach(DIRNAME ${${PROJECT_NAME}_SOURCE_DIRNAMES})
    set(DIR "${PROJECT_SOURCE_DIR}/${DIRNAME}")
    file(GLOB_RECURSE FILES
      "${DIR}/*.cc"
      "${DIR}/*.h")
    list(APPEND ${PROJECT_NAME}_ALL_SOURCE_FILES ${FILES})
  endforeach()
endmacro()
