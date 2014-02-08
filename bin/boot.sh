#!/bin/bash

set -e

PROGRAM="${0}"

while [ -h "${PROGRAM}" ]; do
  LS=`ls -ld "${PROGRAM}"`
  LINK=`expr "${LS}" : '.*-> \(.*\)$'`

  if expr "${LINK}" : '.*/.*' > /dev/null; then
    PROGRAM="${LINK}"
  else
    PROGRAM=`dirname "${PROGRAM}"`/"${LINK}"
  fi
done

DIR=`dirname "${PROGRAM}"`
PROGRAM_DIRECTORY=$(cd "${DIR}" ; pwd)

source "${PROGRAM_DIRECTORY}/vars.sh"

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
DEBUG="guest_errors,int,pcall,unimp,ioport,in_asm"

echo "Booting ${CPU} system with ${RAM} MB RAM from image ${IMAGE} ..."

qemu-system-i386 \
  -cpu "${CPU}" \
  -m "${RAM}" \
  -k en \
  -vga std \
  -no-acpi \
  -no-hpet \
  -d "${DEBUG}" \
  -fda "${IMAGE}"
