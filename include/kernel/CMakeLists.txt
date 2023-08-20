# Kernel include config.

update_parent(TARGET Include
  SOURCES
    "error.h"
    "runtime.h"
    "tty.h"
)

add_platform_subdirectory()
