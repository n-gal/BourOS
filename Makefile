C_SOURCES = $(wildcard Kernel/*.c Drivers/*.c)
HEADERS = $(wildcard Kernel/*.h Drivers/*.h)

# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}

# Change this if your cross-compiler is somewhere else
#CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
#GDB = /usr/local/i386elfgcc/bin/i386-elf-gdb
# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
os-image.bin: Boot/BootSector.bin Kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
Kernel.bin: Boot/KernelEntry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
Kernel.elf: boot/KernelEntry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	i386-elf-gcc -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf Kernel/*.o Boot/*.bin Drivers/*.o boot/*.o