# Kernel config.

add_executable(Kernel
  "main.c"
)

set_target_properties(Kernel
  PROPERTIES
    OUTPUT_NAME kernel.bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_compile_options(Kernel
  PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-O2 -Wall -Wextra -ffreestanding>
)

target_link_options(Kernel
  PRIVATE -N -nostdlib -static -z noexecstack --no-warn-rwx-segments
)

add_platform_subdirectory()
