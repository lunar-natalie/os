# Source directory config.

add_subdirectory(kernel)

if(os_ENABLE_IMAGE)
  add_subdirectory(image)
endif()
