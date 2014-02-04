; 
; A simple boot sector program that demonstrates addressing.
;

[org 0x7c00] ; Tell the assembler where this code will be loaded.

  mov bx, HELLO_MSG ; Use BX as a parameter to our function, so
  call print_string ; we can specify the address of a string.

;  mov dx, 0x1fb6
;  call print_hex

  mov bx, GOODBYE_MSG
  call print_string

  jmp $ ; Infinite loop.

%include "print_string.asm"
%include "print_hex.asm"

; Data

HELLO_MSG:
  db 'Hello, World!', 0
GOODBYE_MSG:
  db 'Goodbye!', 0
  
; Padding and magic BIOS number.

  times 510 - ( $ - $$ ) db 0
  dw 0xaa55
