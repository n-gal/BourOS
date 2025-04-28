@echo off
nasm -f bin ASM/BootSector.asm -o ASM/BootSector.bin
echo Build complete: BootSector.bin generated.
qemu-system-x86_64 ASM/BootSector.bin
echo RunningBourOs.
pause
REM 