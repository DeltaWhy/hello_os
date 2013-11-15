PATH := $(PATH):/opt/cross/bin
AS = i586-elf-as
CC = i586-elf-gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Werror -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -I.
LDFLAGS = -lgcc
ASFLAGS = -g --32

OBJS := $(patsubst %.c,%.o,$(shell find . -maxdepth 1 -name "*.c"))
OBJS += $(patsubst %.s,%.o,$(shell find . -maxdepth 1 -name "*.s"))
OBJS += $(patsubst %.c,%.o,$(shell find hw -name "*.c"))
OBJS += $(patsubst %.s,%.o,$(shell find hw -name "*.s"))
OBJS += $(patsubst %.c,%.o,$(shell find mem -name "*.c"))
OBJS += $(patsubst %.s,%.o,$(shell find mem -name "*.s"))
OBJS += $(patsubst %.c,%.o,$(shell find shell -name "*.c"))
OBJS += $(patsubst %.s,%.o,$(shell find shell -name "*.s"))

KERNELFN = kernel.elf
FLOPPY_IMG = floppy.img

.PHONY: test clean all

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


$(KERNELFN): $(OBJS)
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
