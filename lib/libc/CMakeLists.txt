# libc config.

add_library(Libc
  "strlen.c"
)

set_target_properties(Libc
  PROPERTIES
    OUTPUT_NAME c
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_link_libraries(Libc
  PUBLIC
    Include)
