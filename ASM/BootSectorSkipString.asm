;============BOUROS BOOT SECTOR SKIP STRING==============
; Prints a string to the screen using BIOS interrupts
; Input string registry: 'bx'
;========================================================

SkipString:
    cmp byte [bx], 0
    je FoundEnd
    inc bx
    jmp SkipString

FoundEnd:
    inc bx
    ret