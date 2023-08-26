# Kernel config for i386-pc.

update_parent(TARGET Kernel
  SOURCES
    "boot.s"
    "gdt.c"
    "gdt.s"
    "idt.c"
    "idt.s"
    "isr.s"
    "main.c"
    "tss.c"
    "tss.s"
    "vga.c"
  LINKER_SCRIPT "link.ld"
)

if(${PROJECT_NAME}_ENABLE_TESTS)
  # Check multiboot
  if(GRUB_FILE STREQUAL "GRUB_FILE-NOTFOUND")
    message(WARNING "-- Kernel: unable to test multiboot")
  else()
    add_test(NAME multiboot
      COMMAND ${GRUB_FILE} --is-x86-multiboot $<TARGET_FILE:Kernel>)
  endif()
endif()
