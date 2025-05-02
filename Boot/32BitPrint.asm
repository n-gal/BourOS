;======================32 BIT PRINT======================
; Prints a string to the screen using VGA 
; Input string registry: 'ebx'
;========================================================

[bits 32] ; using 32-bit protected mode

; this is how constants are defined
VIDEO_MEMORY equ 0xb8000

WHITE_ON_BLACK equ 0x0f ; the color byte for each character
GREEN_ON_BLACK equ 0x2 ; 
PrintStringPM:
    pusha
    mov edx, VIDEO_MEMORY

PrintStringPMLoop:
    mov al, [ebx] ; [ebx] is the address of our character
    mov ah, GREEN_ON_BLACK

    cmp al, 0 ; check if end of string
    je PrintSTringPMDone

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 1 ; next char
    add edx, 2 ; next video memory position

    jmp PrintStringPMLoop

PrintSTringPMDone:
    popa
    ret