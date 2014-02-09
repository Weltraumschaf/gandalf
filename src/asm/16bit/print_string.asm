[bits 16]

section .text
  print_string:
    pusha
    mov ah, 0x0e          ; ISR for screen

  .loop:
    mov al, [bx]          ; Store the char at BX in AL
  
    cmp al, 0             ; if (al == 0), at end of string, so
    je .done              ; jump to done
  
    int 0x10
    add bx, 1
    jmp .loop

  .done:  
    popa
    ret
