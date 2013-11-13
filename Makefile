PATH := $(PATH):/opt/cross/bin
AS = i586-elf-as
CC = i586-elf-gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Werror -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -I. -Ipdclib/includes -Ipdclib/platform/hello_os/includes -Ipdclib/internals -Ipdclib/platform/hello_os/internals
LDFLAGS = -lgcc
ASFLAGS = -g --32

OBJS = kernel.o hw/port.o loader.o hw/pic.o hw/screen.o hw/keyboard.o mem/gdt.o mem/setgdt.o hw/idt.o hw/isr_handler.o hw/setidt.o hw/isr_wrapper.o cbuf.o shell/shell.o shell/builtins/bootinfo.o mem/pmm.o mem/vmm.o mem/sbrk.o

KERNELFN = kernel.elf
FLOPPY_IMG = floppy.img

.PHONY: test clean all clean-all

all: $(FLOPPY_IMG) syms

$(FLOPPY_IMG): $(KERNELFN)
	rm -f $@
	cp grub_dos.img $@
	mkdir -p floppy
	sudo mount $@ floppy -o loop,umask=000
	cp $< floppy/boot
	sleep 1
	sudo umount floppy
	rmdir floppy


$(KERNELFN): $(OBJS) pdclib/pdclib.a
	$(CC) $(CFLAGS) -T linker.ld -o $@ $^ $(LDFLAGS)

-include $(OBJS:.o=.d)

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -MD -o $@ -c $<

syms: $(KERNELFN)
	objdump -t $< | sed -nre 's/^([0-9a-f]+).*\s(\S+)$$/\1 \2/p' > $@

test:
	@$(MAKE) -C test test
clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(KERNELFN) $(FLOPPY_IMG) syms
	@$(MAKE) -C test clean

clean-all: clean
	cd pdclib; \
	    PDCLIB_TOOLCHAIN=gcc PDCLIB_PLATFORM=hello_os jam clean -q

pdclib/pdclib.a:
	cd pdclib; \
	    CC=i586-elf-gcc PATH=/opt/cross/bin:/opt/cross/i586-elf/bin:$$PATH PDCLIB_TOOLCHAIN=gcc PDCLIB_PLATFORM=hello_os PDCLIB_NO_TEST=1 /usr/bin/jam -q
