PATH := $(PATH):/opt/cross/bin
CC = i586-elf-gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Werror -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -I.
LDFLAGS = -lgcc

OBJS = kernel.o string.o hw/port.o loader.o hw/pic.o hw/screen.o hw/keyboard.o mem/gdt.o mem/setgdt.o hw/idt.o hw/isr_handler.o hw/setidt.o hw/isr_wrapper.o cbuf.o shell/shell.o shell/builtins/bootinfo.o sprintf.o

KERNELFN = kernel.elf
FLOPPY_IMG = floppy.img

$(FLOPPY_IMG): $(KERNELFN)
	rm -f $@
	cp grub_dos.img $@
	mkdir -p floppy
	sudo mount $@ floppy -o loop,umask=000
	cp $< floppy/boot
	sleep 1
	sudo umount floppy
	rmdir floppy


$(KERNELFN): $(OBJS)
	$(CC) $(CFLAGS) -T linker.ld -o $@ $^ $(LDFLAGS)

.s.o:
	as --32 -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: test clean

test:
	@$(MAKE) -C test test
clean:
	rm -f *.o $(KERNELFN) $(FLOPPY_IMG)
	@$(MAKE) -C test clean
