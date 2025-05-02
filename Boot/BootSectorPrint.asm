;===============BOUROS BOOT SECTOR PRINT=================
; Prints a string to the screen using BIOS interrupts
; Input string registry: 'bx'
;========================================================

Print:
    pusha

; keep this in mind:
; while (string[i] != 0) { print string[i]; i++ }

; the comparison for string end (null byte)
Start:
    mov al, [bx] ; 'bx' is the base address for the string
    cmp al, 0 
    je Done

    ; the part where we print with the BIOS help
    mov ah, 0x0e
    int 0x10 ; 'al' already contains the char

    ; increment pointer and do next loop
    add bx, 1
    jmp Start

Done:
    popa
    ret



PrintNL:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret