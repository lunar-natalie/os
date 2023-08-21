# Kernel include config for i386-pc.

update_parent(TARGET Include
  SOURCES
    "gdt.h"
    "tss.h"
    "vga.h"
)
