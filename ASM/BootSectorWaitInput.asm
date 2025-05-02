;=============BOUROS BOOT SECTOR WAIT INPUT==============
; Waits for the Y key
;========================================================
AwaitInput:
    pusha
    mov ah, 0x0
    int 16h
    
    cmp al, 'Y'
    je AcceptedInput
    cmp al, 'y'
    je AcceptedInput

    call AwaitInput
AcceptedInput:
    popa
    ret