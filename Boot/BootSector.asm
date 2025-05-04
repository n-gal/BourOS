;===================BOUROS BOOT SECTOR===================
; Simple boot sector
;========================================================

; Memory offset from where the boot sector is located
[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ; The same one we used when linking the kernel
mov [BOOT_DRIVE], dl ; Remember that the BIOS sets us the boot drive in 'dl' on boot

mov bp, 0x9000 ; set the stack
mov sp, bp

call PrintNL
mov bx, MSG_TITLE
call Print
call PrintNL

call PrintNL
mov bx, MSG_REAL_MODE
call Print 
call PrintNL

mov bx, MSG_PRESS_TO_CONTINUE ; Press y to continue

call Print 
call PrintNL
call AwaitInput
call PrintNL

call LoadKernel ; read the kernel from the disk
call SwitchToPM ; switch to protected mode
jmp $ ; this will actually never be executed

%include "Boot/BootSectorPrint.asm"
%include "Boot/BootSectorPrintHex.asm"
%include "Boot/BootSectorDisk.asm"
%include "Boot/BootSectorWaitInput.asm"
%include "Boot/32BitGDT.asm"
%include "Boot/32BitSwitch.asm"


[bits 16]
LoadKernel:
    mov bx, MSG_LOAD_KERNEL
    call Print
    call PrintNL

    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 32
    mov dl, [BOOT_DRIVE]
    call DiskLoad
    ret

[bits 32]
BeginPM: ; after the switch we will get here
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $ ; Stay here when the kernel returns control to us (if ever)

BOOT_DRIVE db 0 ;
MSG_TITLE db "BourOS boot sector", 0
MSG_REAL_MODE db "Started in 16-bit", 0
MSG_PRESS_TO_CONTINUE db "press y to boot into 32 bit mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55