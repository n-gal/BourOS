;===================BOUROS BOOT SECTOR===================
; Simple boot sector
;========================================================

; Memory offset from where the boot sector is located
[org 0x7c00]

; The main routine makes sure the parameters are ready and then calls the function

mov bp, 0x8000 ; set the stack safely away from us
mov sp, bp

mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x09000
mov dh, 1 ; read 2 sectors
call DiskLoad

call WriteTitle
call PrintNL
mov bx, VERSION
call Print
call PrintNL



; that's it! we can hang now
jmp $

; remember to include subroutines below the hang
%include "ASM/BootSectorPrint.asm"
%include "ASM/BootSectorPrintHex.asm"
%include "ASM/BootSectorDisk.asm"
%include "ASM/BootSectorSkipString.asm"

WriteTitle:
    call PrintNL
    mov bx, 0x9000
    call Print
    call PrintNL
    call SkipString
    call Print
    call PrintNL
    call SkipString
    call Print
    call PrintNL
    call SkipString
    call Print
    call PrintNL
    call SkipString
    call Print
    ret

; data
TITLE:
    db 'Booting up...', 0

VERSION:
    db 'Ver 1.0', 0

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55


db '    ____                   ____  _____', 0
db '   / __ )____  __  _______/ __ \/ ___/', 0
db '  / __  / __ \/ / / / ___/ / / /\__ \ ', 0
db ' / /_/ / /_/ / /_/ / /  / /_/ /___/ / ', 0
db '/_____/\____/\__,_/_/   \____//____/  ', 0
