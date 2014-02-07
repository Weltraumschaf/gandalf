#!/bin/bash

SRC="${PROGRAM_DIRECTORY}/../src"
SRC_ASM="${SRC}/asm"
SRC_C="${SRC}/c"

TARGET="${PROGRAM_DIRECTORY}/../target"

KERNEL_OFFSET="0x1000"
KERNEL_SRC="${SRC_C}/kernel.c"
KERNEL_OBJ="${TARGET}/kernel.o"
KERNEL_BIN="${TARGET}/kernel.bin"

BOOT_SRC="${SRC_ASM}/boot_sector.asm"
BOOT_BIN="${TARGET}/boot_sector.bin"

IMAGE="${TARGET}/os.img"