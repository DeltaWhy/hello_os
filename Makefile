MAKE = make
CC = gcc
CFLAGS = -std=c99 -m32 -Wall -Wextra -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
LD = ld

OBJS = kernel.o string.o hw/port.o loader.o hw/pic.o hw/screen.o hw/keyboard.o mem/gdt.o mem/setgdt.o hw/idt.o hw/isr_handler.o hw/setidt.o hw/isr_wrapper.o cbuf.o shell/shell.o

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
	$(LD) -melf_i386 -T linker.ld -o $@ $^

.s.o:
	as --32 -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: test clean

test:
	@$(MAKE) -C test test
clean:
	-rm $(OBJS) $(KERNELFN) $(FLOPPY_IMG)
	@$(MAKE) -C test clean
