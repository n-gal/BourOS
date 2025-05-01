;============BOUROS BOOT SECTOR SKIP STRING==============
; Skips to the next string
; Input string registry: 'bx' - position of the string
; Output string registry: 'bx' - position of the next string
;========================================================

SkipString:
    cmp byte [bx], 0
    je FoundEnd
    inc bx
    jmp SkipString

FoundEnd:
    inc bx
    ret