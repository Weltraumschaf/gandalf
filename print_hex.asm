print_hex:
  mov bx, HEX_OUT
  call print_string
  ret

; Data

HEX_OUT:
  db '0x0000', 0
