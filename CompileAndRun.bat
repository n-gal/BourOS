@echo off
REM Build the kernel
echo Assembling KernelEntry.asm...
nasm Boot/KernelEntry.asm -f elf -o Bin/KernelEntry.o
if errorlevel 1 goto error

echo Compiling Kernel.c...
i386-elf-gcc -ffreestanding -m32 -c Kernel/Kernel.c -o Bin/Kernel.o
if errorlevel 1 goto error

echo Linking Kernel.bin...
i386-elf-ld -o Bin/Kernel.bin -Ttext 0x1000 Bin/KernelEntry.o Bin/Kernel.o --oformat binary
if errorlevel 1 goto error

REM Build boot sector
echo Assembling BootSector.asm...
nasm Boot/BootSector.asm -f bin -o Bin/BootSector.bin
if errorlevel 1 goto error

REM Combine boot and kernel into os image
echo Combining to os-image.bin...


copy /b "Bin\BootSector.bin"+"Bin\Kernel.bin" "Bin\os-image.bin" > nul
if errorlevel 1 goto error

REM Optional: disassemble
REM echo Disassembling kernel.bin...
REM ndisasm -b 32 kernel.bin > kernel.dis

REM Run in QEMU
echo Running QEMU...
qemu-system-i386 -fda Bin/os-image.bin
goto end

:error
echo.
echo [ERROR] Build failed.
goto end

:end