#
# Builds the kernel.
#

# Cross compiler
CC  	:= ./build-tools/cross/bin/i586-elf-gcc
CXX 	:= ./build-tools/cross/bin/i586-elf-g++
CPP 	:= ./build-tools/cross/bin/i586-elf-cpp
LD  	:= ./build-tools/cross/bin/i586-elf-ld
AS		:= nasm
DISAS	:= ndisasm

# Default CFLAGS:
CFLAGS	?= -O2 -g

# Add mandatory options to CFLAGS:
CFLAGS	:= $(CFLAGS) -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes

# VN
QEMU	:= qemu-system-i386

# Variables
SRC_DIR	    := src
C_SRC_DIR   := $(SRC_DIR)/c
ASM_SRC_DIR := $(SRC_DIR)/asm

#
# Targets
#

all : os.img

CPU = 486
RAM = 32
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
DEBUG = guest_errors,int,pcall,unimp,ioport,in_asm

run : all

	$(QEMU) \
	  -cpu $(CPU) \
	  -m $(RAM) \
	  -k en \
	  -vga std \
	  -no-acpi \
	  -no-hpet \
	  -d $(DEBUG) \
	  -fda os.img
	  
debug : all

	$(QEMU) -gdb tcp::1234 -S \
	  -cpu $(CPU) \
	  -m $(RAM) \
	  -k en \
	  -vga std \
	  -no-acpi \
	  -no-hpet \
	  -d $(DEBUG) \
	  -fda os.img
	  
# Automatically generate lists of sources using wildcards.
C_SOURCES := $(shell find $(C_SRC_DIR) -name "*.c" -print)
HEADERS := $(filter_out */provided/* ,$(shell find $(C_SRC_DIR) -name "*.h" -print))

# Create a list of object files to build, simple by replacing
# the '.c' extension of filenames in C_SOURCES with '.o'
OBJ = ${C_SOURCES:.c=.o}

# This is the actual disk image that the computer loads,
# which is the combination of our compiled bootsector and kernel
os.img : boot_sector.bin kernel.bin
	cat $^ > os.img

# This links the binary of our kernel from two object files:
# - the kernel_entry, which jumps to main() in our kernel
# - the compiled C kernel
kernel.bin: kernel_entry.o ${OBJ}
	$(LD) $^ -o $@ -Ttext 0x1000 --oformat binary

# Generic rule for building 'somefile.o' from 'somefile.c'
%.o : %.c ${HEADERS}
	$(CC) -ffreestanding -std=gnu99 -c $< -o $@

# Build the kernel entry object file.
kernel_entry.o : $(ASM_SRC_DIR)/kernel_entry.asm
	$(AS) $< -f elf -o $@

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly
# routines that we include in boot_sect.asm
boot_sector.bin : $(ASM_SRC_DIR)/boot_sector.asm
	$(AS) $< -f bin -o $@

clean :
	$(RM) -v *.bin *.img *.map *.dis
	find $(SRC_DIR) -name "*.o" -exec $(RM) -rv {} \;

# Disassemble our kernel - might be useful for debugging.
kernel.dis : kernel.bin
	$(DISAS) -b 32 $< > $@
