print_string:
  pusha
  mov ah, 0x0e

loop_start:
  mov al, [bx]
  cmp al, 0
  je leave_function
  int 0x10
  add bx, 0x01
  jmp loop_start
leave_function:
  popa
  ret
