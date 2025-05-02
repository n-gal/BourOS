[bits 32]
[extern main]

global _start
_start:
    cli             ; Clear interrupts
    xor ebp, ebp    ; Clear base pointer
    mov esp, 0x90000 ; Set up a temporary stack (must match whatever you’re using)
    call main       ; Call your C function

hang:
    jmp hang        ; Prevent exit