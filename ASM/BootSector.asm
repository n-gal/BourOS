;===================BOUROS BOOT SECTOR===================
; Simple boot sector
;========================================================

; Memory offset from where the boot sector is located
[org 0x7c00]

mov bp, 0x8000 ; set the stack
mov sp, bp

mov bx, 0x9000
mov dh, 1
call DiskLoad
call WriteTitle

call PrintNL
mov bx, MSG_REAL_MODE
call Print ; This will be written after the BIOS messages

call SwitchToPM ; switch to protected mode
jmp $ ; this will actually never be executed

; remember to include subroutines below the hang
%include "ASM/BootSectorPrint.asm"
%include "ASM/BootSectorPrintHex.asm"
%include "ASM/BootSectorDisk.asm"
%include "ASM/BootSectorSkipString.asm"
%include "ASM/BootSectorTitle.asm"
%include "ASM/32BitPrint.asm"
%include "ASM/32BitGDT.asm"
%include "ASM/32BitSwitch.asm"

; data
TITLE:
    db 'Booting up...', 0

VERSION:
    db 'Ver 1.1', 0


[bits 32]
BeginPM: ; after the switch we will get here
    mov ebx, MSG_PROT_MODE
    call PrintStringPM ; Note that this will be written at the top left corner
    jmp $


MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55


db '    ____                   ____  _____', 0
db '   / __ )____  __  _______/ __ \/ ___/', 0
db '  / __  / __ \/ / / / ___/ / / /\__ \ ', 0
db ' / /_/ / /_/ / /_/ / /  / /_/ /___/ / ', 0
db '/_____/\____/\__,_/_/   \____//____/  ', 0
