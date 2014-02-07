#!/bin/bash

IMAGE="./boot_sector.bin"
CPU="486"
RAM="32"
# out_asm       show generated host assembly code for each compiled TB
# in_asm        show target assembly code for each compiled TB
# op            show micro ops for each compiled TB
# op_opt        show micro ops (x86 only: before eflags optimization) and
#               after liveness analysis
# int           show interrupts/exceptions in short format
# exec          show trace before each executed TB (lots of logs)
# cpu           show CPU state before block translation
# pcall         x86 only: show protected mode far calls/returns/exceptions
# cpu_reset     x86 only: show CPU state before CPU resets
# ioport        show all i/o ports accesses
# unimp         log unimplemented functionality
# guest_errors  log when the guest OS does something invalid (eg accessing a
#               non-existent register)
DEBUG="guest_errors,int,pcall,unimp,ioport"

echo "Booting ${CPU} system with ${RAM} MB RAM from image ${IMAGE} ..."

qemu-system-i386 \
  -cpu ${CPU} \
  -m ${RAM} \
  -k en \
  -vga std \
  -no-acpi \
  -no-hpet \
  -d ${DEBUG} \
  "${IMAGE}"
