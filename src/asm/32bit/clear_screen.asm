[bits 32]

section .text
  clear_screen:
    pusha
    cld

    mov edi, VIDEO_MEMORY
    mov cx, 2000
    mov ah, WHITE_ON_BLACK
    mov al, ' '
    rep stosw
  
    popa
    ret
