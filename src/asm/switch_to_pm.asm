[bits 16]
; Switch to protected mode
switch_to_pm:
  mov bx, MSG_SW_OFF_INT
  call print_string
  
  cli                   ; We must switch of interrupts until we have 
                        ; set-up the protected mode interrupt vector
                        ; otherwise interrupts will run riot.

  mov bx, MSG_LOAD_GDT
  call print_string

  mov bx, MSG_SW_PM
  call print_string
    
  lgdt [gdt_descriptor] ; Load our global descriptor table, which defines
                        ; the protected mode segments (e.g. for code and data)
  mov eax, cr0          ; To make the switch to protected mode, we set
  or eax, 0x1           ; the first bit of CR0, a control register
  mov cr0, eax
  
  jmp CODE_SEG:init_pm  ; Make a far jump (i.e. to a new segment) to our 32-bit
                        ; code. This also forces the CPU to flush its cache of
                        ; pre-fetched and real-mode decoded instructions, which 
                        ; can cause problems.

MSG_SW_OFF_INT: db 'Switching off interrupts ...', 13, 10, 0
MSG_LOAD_GDT:   db 'Loading global descriptor table ...', 13, 10, 0
MSG_SW_PM:      db 'Switching into protected mode ...', 13, 10, 0

[bits 32]
; Initialise registers and the stack once in PM.
init_pm:
  mov ax, DATA_SEG      ; Now in PM , our old segments are meaningless, 
  mov ds, ax            ; so we point our segment registers to the
  mov ss, ax            ; data selector we defined in our GDT
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov ebp, 0x90000      ; Update our stack position so it is right
  mov esp, ebp          ; at the top of the free space.
  
  call BEGIN_PM         ; Finally, call some well-known label
  
; Define some video constants.
VIDEO_MEMORY    equ 0xb8000
WHITE_ON_BLACK  equ 0x0f
