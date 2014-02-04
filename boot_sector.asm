; 
; Asimple boot sector
;

foo:

jmp foo

times 510 - ( $ - $$ ) db 0

dw 0xaa55
