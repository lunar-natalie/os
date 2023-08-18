# ClangTidy CMake target.
# Lints code in each created C target.

find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY STREQUAL "CLANG_TIDY-NOTFOUND")
  message("-- ClangTidy not found")
else()
  message("-- Found ClangTidy: ${CLANG_TIDY}")

  set(HEADER_FILTER ".")

  set(CMAKE_C_CLANG_TIDY
    ${CLANG_TIDY};
    -header-filter='${HEADER_FILTER}';
    -p ${CMAKE_BINARY_DIR})
endif()
