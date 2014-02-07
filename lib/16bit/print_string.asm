[bits 16]

print_string:
  pusha
  mov ah, 0x0e

loop_start:
  mov al, [bx]
  cmp al, 0
  je leave_function
  int 0x10
  add bx, 1
  jmp loop_start

leave_function:
  mov al, 0x0a ; Print LF
  int 0x10
  mov al, 0x0d ; Print CR
  int 0x10
  popa
  ret
