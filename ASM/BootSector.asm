;===================BOUROS BOOT SECTOR===================
; Simple boot sector
;========================================================

; Memory offset from where the boot sector is located
[org 0x7c00]

mov ah, 0x0e ; tty mode

mov al, 'B'
int 0x10

mov al, 'o'
int 0x10

mov al, 'u'
int 0x10

mov al, 'r'
int 0x10

mov al, 'O'
int 0x10

mov al, 'S'
int 0x10

jmp $ ; jump to current address = infinite loop

; padding and magic number
; these are compile time directives, it makes the assembler fill the rest of the file with 0s until it reaches 510 bytes
; this means that the file has to be 512 bytes long, 0xaa55 is read by the BIOS to know that it is a boot sector
times 510 - ($-$$) db 0
dw 0xaa55 