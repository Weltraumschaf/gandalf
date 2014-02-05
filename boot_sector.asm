; 
; A simple boot sector program that demonstrates addressing.
;

[org 0x7c00] ; Tell the assembler where this code will be loaded.

  mov bx, HELLO_MSG       ; Use BX as a parameter to our function, so
  call print_string       ; we can specify the address of a string.

  mov [BOOT_DRIVE], dl    ; BIOS stores our boot drive in DL, so it's 
                          ; best to remember this forlater.
  
  mov bp, 0x8000          ; Here we set our stack safely out of the
  mov sp, bp              ; way, at 0x8000.
  
  mov bx, 0x9000          ; Load 2 sectors to 0x0000(ES):0x9000(BX)
  mov dh, 2               ; from the boot disk.
  mov dl, [BOOT_DRIVE]
  call disk_load
  
  mov dx, [0x9000]        ; Print out the first loaded word, which
  call print_hex          ; we expect to be 0xdada, stored at adress 0x9000.
  
  mov dx, [0x9000 + 512]  ; Also, print the first word from the 
  call print_hex          ; 2nd loaded sector: should be 0xface
  
  mov bx, GOODBYE_MSG
  call print_string

  jmp $ ; Infinite loop.

%include "print_string.asm"
%include "print_hex.asm"
%include "disk_load.asm"

; Data

HELLO_MSG:    db 'Hello, World!', 0
GOODBYE_MSG:  db 'Goodbye!', 0
BOOT_DRIVE:   db 0
  
; Padding and magic BIOS number.

  times 510 - ( $ - $$ ) db 0
  dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface
