# Kernel config for x86_64-pc.

update_parent(TARGET Kernel
  SOURCES
    "boot.s"
  LINKER_SCRIPT "link.ld"
)

if(${PROJECT_NAME}_ENABLE_TESTS)
  # Check multiboot
  if(GRUB_FILE STREQUAL "GRUB_FILE-NOTFOUND")
    message(WARNING "-- Kernel: unable to test multiboot")
  else()
    add_test(NAME multiboot
      COMMAND ${GRUB_FILE} --is-x86-multiboot $<TARGET_FILE:Kernel>)
    message("-- Kernel: enabled multiboot test")
  endif()
endif()
