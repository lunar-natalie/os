# libc config.

add_library(Libc
  "stdio/printf.c"
  "string/memcpy.c"
  "string/strlen.c"
)

set_target_properties(Libc
  PROPERTIES
    OUTPUT_NAME c
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_link_libraries(Libc
  PUBLIC
    Include)
