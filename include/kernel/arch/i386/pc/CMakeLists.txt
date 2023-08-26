# Kernel include config for i386-pc.

update_parent(TARGET Include
  SOURCES
    "except.h"
    "gdt.h"
    "idt.h"
    "tss.h"
    "vga.h"
)
