# Boot image config.

# Generate GRUB config.
file(READ iso/boot/grub/grub.cfg.in GRUB_CFG)

file(GENERATE
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg
  CONTENT ${GRUB_CFG})

set(ISO_DIR ${CMAKE_CURRENT_BINARY_DIR}/iso)

add_custom_target(Image ALL
  COMMAND cp $<TARGET_FILE:Kernel> ${ISO_DIR}/boot/${KERNEL_NAME}
  COMMAND grub-mkrescue -o ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.iso ${ISO_DIR}
  DEPENDS Kernel)
