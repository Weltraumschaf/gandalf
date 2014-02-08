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
	qemu-system-i386 \
	  -cpu $(CPU) \
	  -m $(RAM) \
	  -k en \
	  -vga std \
	  -no-acpi \
	  -no-hpet \
	  -d $(DEBUG) \
	  -fda os.img


# Automatically generate lists of sources using wildcards. 
C_SOURCES = $(wildcard src/c/kernel/*.c src/c/drivers/*.c)
HEADERS = $(wildcard src/c/kernel/*.h src/c/drivers/*.h)
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
	$(CC) -ffreestanding -c $< -o $@

# Build the kernel entry object file.
kernel_entry.o : src/asm/kernel_entry.asm
	nasm $< -f elf -o $@

# Assemble the boot sector to raw machine code
# The -I options tells nasm where to find our useful assembly 
# routines that we include in boot_sect.asm
boot_sector.bin : src/asm/boot_sector.asm
	nasm $< -f bin -o $@

clean :
	$(RM) *.o *.bin *.img *.map *.dis
	$(RM) src/c/kernel/*.o src/c/drivers/*.o
	
# Disassemble our kernel - might be useful for debugging.
kernel.dis : kernel.bin 
	ndisasm -b 32 $< > $@
