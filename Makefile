#
# Builds the kernel.
#

CWD = $(shell pwd)
$(info CWD is $(CWD))

# Cross compiler
BUILD_TOOLS_PREFIX := $(CWD)/build-tools/cross/bin/i586-elf-
CC  	:= $(BUILD_TOOLS_PREFIX)gcc
CXX 	:= $(BUILD_TOOLS_PREFIX)g++
CPP 	:= $(BUILD_TOOLS_PREFIX)cpp
LD  	:= $(BUILD_TOOLS_PREFIX)ld
AS		:= nasm
DISAS	:= ndisasm

$(info CC is $(CC))
$(info CXX is $(CXX))
$(info CPP is $(CPP))
$(info LD is $(LD))

# Default CFLAGS, if nothing set by CLI:
# -g	w/ debug symbols
# -O2	optimization
CFLAGS	?= -O2 -g

# Add mandatory options to CFLAGS:
CFLAGS	:= $(CFLAGS) -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes
$(info CFLAGS is $(CFLAGS))

#
# VN options.
#
QEMU_BIN	:= qemu-system-i386
QEMU_CPU    := 486
QEMU_RAM    := 32
QEMU_KEYMAP := en-us
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
QEMU_DEBUG      := cpu
QEMU_GDB_PORT   := tcp::1234

# Variables
SRC_DIR	    := src
C_SRC_DIR   := $(SRC_DIR)/c
ASM_SRC_DIR := $(SRC_DIR)/asm

OUTPUT_IMAGE := gandalf.img

#
# Targets
#

all : image

run : all

	$(QEMU_BIN) \
		-cpu $(QEMU_CPU) \
		-m $(QEMU_RAM) \
		-k $(QEMU_KEYMAP) \
		-vga std \
		-no-acpi \
		-no-hpet \
		-fda $(OUTPUT_IMAGE)

debug : all

	$(QEMU_BIN) -gdb $(QEMU_GDB_PORT) -S \
		-cpu $(QEMU_CPU) \
		-m $(QEMU_RAM) \
		-k $(QEMU_KEYMAP) \
		-vga std \
		-no-acpi \
		-no-hpet \
		-d $(QEMU_DEBUG) \
		-fda $(OUTPUT_IMAGE)

KERNEL_HEADERS	= $(C_SRC_DIR)/include
LIBC_HEADERS	= $(C_SRC_DIR)/libc/include

# Automatically generate lists of sources using wildcards.
C_SOURCES	:= $(shell find $(C_SRC_DIR) -name "*.c" -print)
HEADERS		:= $(filter_out */provided/* ,$(shell find $(C_SRC_DIR) -name "*.h" -print))

# Create a list of object files to build, simple by replacing
# the '.c' extension of filenames in C_SOURCES with '.o'
OBJ = ${C_SOURCES:.c=.o}

# This is the actual disk image that the computer loads,
# which is the combination of our compiled bootsector and kernel
image : boot_sector.bin kernel.bin
	cat $^ > $(OUTPUT_IMAGE)

# This links the binary of our kernel from two object files:
# - the kernel_entry, which jumps to main() in our kernel
# - the compiled C kernel
kernel.bin: kernel_entry.o ${OBJ}
	$(LD) $^ -o $@ -Ttext 0x1000 --oformat binary

# Generic rule for building 'somefile.o' from 'somefile.c'
%.o : %.c ${HEADERS}
	$(CC) -ffreestanding -std=gnu99 \
		-I$(KERNEL_HEADERS) \
		-I$(LIBC_HEADERS) \
		-c $< -o $@

# Build the kernel entry object file.
kernel_entry.o : $(ASM_SRC_DIR)/kernel_entry.asm
	$(AS) $< -f elf -o $@

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly
# routines that we include in boot_sect.asm
boot_sector.bin : $(ASM_SRC_DIR)/boot_sector.asm
	$(AS) $< -f bin -o $@

clean :
	$(RM) -v *.bin *.img *.map *.dis *.o
	find $(SRC_DIR) -name "*.o" -exec $(RM) -rv {} \;

# Disassemble our kernel - might be useful for debugging.
kernel.dis : kernel.bin
	$(DISAS) -b 32 $< > $@
