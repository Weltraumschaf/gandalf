[bits 16]

print_string:
  pusha
  mov ah, 0x0e          ; ISR for screen

print_string_loop:
  mov al, [bx]          ; Store the char at BX in AL
  
  cmp al, 0             ; if (al == 0), at end of string, so
  je print_string_done  ; jump to done
  
  int 0x10
  add bx, 1
  jmp print_string_loop

print_string_done:
  mov al, 0x0a ; Print LF
  int 0x10
  
  mov al, 0x0d ; Print CR
  int 0x10
  
  popa
  ret
