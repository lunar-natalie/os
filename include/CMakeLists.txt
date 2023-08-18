# Include directory config.

add_library(Include INTERFACE)

target_sources(Include PUBLIC FILE_SET HEADERS
  BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
  FILES
    "string.h"
)

add_subdirectory(kernel)
