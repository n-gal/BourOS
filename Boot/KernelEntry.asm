[bits 32]
[extern Main]

global _start
_start:
    cli             ; Clear interrupts
    xor ebp, ebp    ; Clear base pointer
    mov esp, 0x90000 ; Set up a temporary stack (must match whatever you’re using)
    call Main       ; Call your C function
    jmp hang

hang:
    jmp hang        ; Prevent exit