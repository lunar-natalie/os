# ClangFormat CMake target.
# Formats all C code in the project.

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT STREQUAL "CLANG_FORMAT-NOTFOUND")
  message("-- ClangFormat not found")
else()
  message("-- Found ClangFormat: ${CLANG_FORMAT}")
  add_custom_target(ClangFormat
    COMMAND ${CLANG_FORMAT} -i ${${PROJECT_NAME}_ALL_SOURCE_FILES})
endif()
