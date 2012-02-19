CC=i586-elf-gcc  -std=gnuc99
CFLAGS=-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -c
LD=i586-elf-ld
LFLAGS=-T linker.ld
ASM=nasm
RLIBC=rlibc.a
AR=i586-elf-ar
all:
	$(MAKE) -C kernel kernel
clean:
	$(MAKE) -C kernel clean
run:all
	$(MAKE) -C kernel run