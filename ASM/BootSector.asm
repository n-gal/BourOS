;===================BOUROS BOOT SECTOR===================
; Simple boot sector
;========================================================

; Memory offset from where the boot sector is located
[org 0x7c00]

; The main routine makes sure the parameters are ready and then calls the function
mov bx, TITLE
call print

call print_nl
mov bx, VERSION
call print

; that's it! we can hang now
jmp $

; remember to include subroutines below the hang
%include "ASM/BootSectorPrint.asm"
%include "ASM/BootSectorPrintHex.asm"


; data
TITLE:
    db 'BourOS', 0

VERSION:
    db 'Ver 1.0', 0

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55