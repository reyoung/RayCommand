CC=i586-elf-gcc -std=c99
CFLAGS=-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -c -Ibasecrt
LD=i586-elf-ld
LFLAGS=-T linker.ld
AS=nasm
AS_FLAG= -f elf
ASM_SOURCE_FILES=$(wildcard *.S) $(wildcard driver/X86_arch/*.S)
C_SOURCE_FILES=$(wildcard *.c) $(wildcard driver/console/*.c) $(wildcard driver/X86_arch/*.c)
OBJS=$(patsubst %.c,%.o,$(C_SOURCE_FILES)) $(patsubst %.S,%.o,$(ASM_SOURCE_FILES))


run:kernel
	qemu.exe -vga std -kernel ../bin/kernel.bin
kernel: $(OBJS)
	$(LD) $(LFLAGS) -o ../bin/kernel.bin $(OBJS)
clean:
	rm ../bin/kernel.bin
	rm $(OBJS)
%.o:%.c
	$(CC) $(CFLAGS) -o  $@ $(INCLUDE_OPTIONS) $<
%.o:%.S
	$(AS) $(AS_FLAG) -o $@ $<

