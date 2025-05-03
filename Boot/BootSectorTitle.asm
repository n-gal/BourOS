;===============BOUROS BOOT SECTOR TITLE=================
; Draws the title
;========================================================
WriteTitle:
    pusha
    call PrintNL
    mov bx, 0x7E00
    mov dh, 1
    call Print
    Loop: 
        call PrintNL
        call SkipString
        call Print
        inc dh
        cmp dh, 5
        jl Loop
    call PrintNL
    popa
    ret