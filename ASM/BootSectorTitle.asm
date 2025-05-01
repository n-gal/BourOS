;===============BOUROS BOOT SECTOR TITLE=================
; Draws the title
;========================================================
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
    call PrintNL
    ret