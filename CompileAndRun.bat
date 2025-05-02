@echo off
REM Build the kernel
echo Assembling KernelEntry.asm...
nasm ASM/KernelEntry.asm -f elf -o ASM/KernelEntry.o
if errorlevel 1 goto error

echo Compiling Kernel.c...
i386-elf-gcc -ffreestanding -m32 -c ASM/Kernel.c -o ASM/Kernel.o
if errorlevel 1 goto error

echo Linking Kernel.bin...
i386-elf-ld -o ASM/Kernel.bin -Ttext 0x1000 ASM/KernelEntry.o ASM/Kernel.o --oformat binary
if errorlevel 1 goto error

REM Build boot sector
echo Assembling BootSector.asm...
nasm ASM/BootSector.asm -f bin -o ASM/BootSector.bin
if errorlevel 1 goto error

REM Combine boot and kernel into os image
echo Combining to os-image.bin...


copy /b "ASM\BootSector.bin"+"ASM\Kernel.bin" "ASM\os-image.bin" > nul
if errorlevel 1 goto error

REM Optional: disassemble
REM echo Disassembling kernel.bin...
REM ndisasm -b 32 kernel.bin > kernel.dis

REM Run in QEMU
echo Running QEMU...
qemu-system-i386 -fda ASM/os-image.bin
goto end

:error
echo.
echo [ERROR] Build failed.
goto end

:end