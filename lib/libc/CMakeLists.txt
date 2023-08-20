# libc config.

add_library(Libc
  "stdio/printf.c"
  "string/memcpy.c"
  "string/memset.c"
  "string/strlen.c"
)

set_target_properties(Libc
  PROPERTIES
    OUTPUT_NAME c
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_compile_options(Libc
  PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-O2 -Wall -Wextra -ffreestanding>
)

target_link_options(Libc
  PRIVATE -nostdlib
)

target_link_libraries(Libc
  PUBLIC
    Include)
