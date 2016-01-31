; The boot sector.
[org 0x7c00] ; Tell the assembler where this code will be loaded.
  KERNEL_OFFSET equ 0x1000  ; This is the memory offset to which 
                            ; we will load our kernel

  mov [BOOT_DRIVE], dl      ; BIOS stores our boot drive in DL, so it’s
                            ; best to remember this for later.

  mov bp, 0x9000            ; Set the stack.
  mov sp, bp
  
  mov bx, MSG_REAL_MODE
  call print_string
  call load_kernel          ; Load our kernel
  call switch_to_pm         ; Note that we never return from here.
  jmp $                     ; Infinite loop.

%include "src/asm/16bit/print_string.asm"
%include "src/asm/16bit/disk_load.asm"
%include "src/asm/gdt.asm"
%include "src/asm/switch_to_pm.asm"
%include "src/asm/32bit/print_string_pm.asm"

[bits 16]
load_kernel:
  mov bx, MSG_LOAD_KERNEL     ; Print a message to say we are loading the kernel.
  call print_string
  
  mov bx, KERNEL_OFFSET       ; Set -up parameters for our disk_load routine , so
  mov dh , 15                 ; that we load the first 15 sectors (excluding
  mov dl, [BOOT_DRIVE]        ; the boot sector) from the boot disk (i.e. our
  call disk_load              ; kernel code) to address KERNEL_OFFSET

  ret 
  
[bits 32]
; This is where we arrive after switching to and initialising protected mode.
BEGIN_PM:
  mov ebx, MSG_PROT_MODE
  call print_string_pm
  
  call KERNEL_OFFSET            ; Now jump to the address of our loaded
                                ; kernel code, assume the brace position, 
                                ; and cross your fingers. Here we go!
  jmp $                         ; Infinite loop.

; Data
MSG_REAL_MODE:  db "Started in 16-bit Real Mode.", 0
MSG_PROT_MODE:  db "Successfully landed in 32-bit Protected Mode", 0
BOOT_DRIVE:     db 0
MSG_LOAD_KERNEL db "Loading kernel into memory.", 0

; Padding and magic BIOS number.
  times 510 - ( $ - $$ ) db 0
  dw 0xaa55
