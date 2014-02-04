; 
; A simple boot sector program that demonstrates addressing.
;

[org 0x7c00]

  mov ah, 0x0e    ; int 10/ah = 0eh -> scrolling teletype BIOS routine
  
  mov bp, 0x8000  ; Set the base of the stack a little above where BIOS
  mov sp, bp      ; loads our boot sector - so it won’t overwrite us.
  
  push 'A'
  push 'B'
  push 'C'
  
  pop bx
  mov al, bl
  int 0x10
  
  pop bx
  mov al, bl
  int 0x10
  
  mov al, [0x7ffe]
  int 0x10
  
  jmp $

; Padding and magic BIOS number.

  times 510 - ( $ - $$ ) db 0
  dw 0xaa55
