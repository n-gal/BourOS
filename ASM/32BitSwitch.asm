;======================32 BIT Switch=====================
; Switches from 16 bit mode to 32 bit
;========================================================

[bits 16]
SwitchToPM:
    cli ; 1. disable interrupts
    lgdt [GDTDescriptor] ; 2. load the GDT descriptor
    mov eax, cr0
    or eax, 0x001 ; 3. set 32-bit mode bit in cr0
    mov cr0, eax
    jmp CODE_SEG:InitPM ; 4. far jump by using a different segment

[bits 32]
InitPM: ; we are now using 32-bit instructions
    mov ax, DATA_SEG ; 5. update the segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; 6. update the stack right at the top of the free space
    mov esp, ebp

    call BeginPM ; 7. Call a well-known label with useful code