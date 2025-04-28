@echo off
nasm -f bin ASM/BootSector.asm -o ASM/BootSector.bin
echo Build complete: BootSector.bin generated.
pause
REM 