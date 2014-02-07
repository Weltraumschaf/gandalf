; The boot sector.
[org 0x7c00] ; Tell the assembler where this code will be loaded.
  mov bp, 0x9000        ; Set the stack.
  mov sp, bp
  
  mov bx, MSG_REAL_MODE
  call print_string
  
  call switch_to_pm     ; Note that we never return from here.
  jmp $                 ; Infinite loop.

%include "lib/16bit/print_string.asm"
%include "lib/gdt.asm"
%include "lib/switch_to_pm.asm"
%include "lib/32bit/print_string_pm.asm"
%include "lib/32bit/clear_screen.asm"

[bits 32]
; This is where we arrive after switching to and initialising protected mode.
BEGIN_PM:
  call clear_screen
  mov ebx, MSG_PROT_MODE
  
  call print_string_pm
  jmp $                   ; Infinite loop.

; Data
MSG_REAL_MODE:  db "Started in 16-bit Real Mode.", 0
MSG_PROT_MODE:  db "Successfully landed in 32-bit Protected Mode", 0
  
; Padding and magic BIOS number.
  times 510 - ( $ - $$ ) db 0
  dw 0xaa55
