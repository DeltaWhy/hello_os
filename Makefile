CC = gcc
CFLAGS = -std=c99 -m32 -Wall -Wextra -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
LD = ld

OBJS = kernel.o io.o loader.o pic.o string.o keyboard.o gdt.o setgdt.o

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

clean:
	rm -f $(OBJS) $(KERNELFN) $(FLOPPY_IMG)
