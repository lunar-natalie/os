# ClangTidy CMake target.
# Lints code in each created C target.

find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY STREQUAL "CLANG_TIDY-NOTFOUND")
  message("-- ClangTidy not found")
else()
  message("-- Found ClangTidy: ${CLANG_TIDY}")

  set(HEADER_FILTER "")
  set(USE_HEADER_FILTER OFF)
  foreach(DIRNAME ${${PROJECT_NAME}_SOURCE_DIRNAMES})
    list(APPEND HEADER_FILTER "${DIRNAME}/*.h")
    file(GLOB_RECURSE DIR_FILES "${DIRNAME}/*.h")
    if(NOT(DIR_FILES STREQUAL ""))
      set(USE_HEADER_FILTER ON)
    endif()
  endforeach()

  set(CMAKE_C_CLANG_TIDY
    ${CLANG_TIDY};
    -p ${CMAKE_BINARY_DIR})
  if(USE_HEADER_FILTER)
    list(APPEND CMAKE_C_CLANG_TIDY -header-filter='${HEADER_FILTER}')
  endif()
endif()
