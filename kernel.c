#include <stdint.h>
#include "string.h"
#include "mboot.h"
#include "hw/pic.h"
#include "hw/port.h"
#include "hw/keyboard.h"
#include "hw/screen.h"
#include "hw/idt.h"
#include "mem/gdt.h"
#include "shell/shell.h"
#define UNUSED(x) (void)x
void exit(void);

void print_mboot_info(mboot_info *mbd) {
    char tmp[64];
    print("Multiboot flags: 0x");
    itoa(mbd->flags, tmp, 16);
    print(tmp);
    print("\nLow memory: ");
    itoa(mbd->mem_lo, tmp, 10);
    print(tmp);
    print("K    High memory: ");
    itoa(mbd->mem_hi, tmp, 10);
    print(tmp);
    print("K\nKernel command line: ");
    print(mbd->cmd_line);
    print("\nBootloader name: ");
    print(mbd->bootloader_name);
    print("\nMemory map:\n");
    mboot_mmap_entry *e = mbd->mmap_addr;
    while (((uint32_t)e) < ((uint32_t)mbd->mmap_addr) + mbd->mmap_length) {
        print("    0x");
        itoa((uint32_t)e, tmp, 16);
        print(tmp);
        print("\n    Entry size=");
        itoa(e->size, tmp, 10);
        print(tmp);
        print(" base=0x");
        itoa(e->addr_hi, tmp, 16);
        print(tmp);
        itoa(e->addr_lo, tmp, 16);
        print(tmp);
        print("\n        length=0x");
        itoa(e->len_hi, tmp, 16);
        print(tmp);
        itoa(e->len_lo, tmp, 16);
        print(tmp);
        print(" type: 0x");
        itoa(e->type, tmp, 16);
        print(tmp);
        print("\n");
        e = (mboot_mmap_entry *)((uint32_t)e + e->size + 4);
    }
}

void kmain(mboot_info *mbd, uint32_t magic) {
    UNUSED(mbd);
    if ( magic != 0x2BADB002 )
    {
    	print("Something went not according to specs.");
		exit();
    }

	kclear();
        print("initializing GDT...\n");
        init_gdt();
        print("initializing IDT...\n");
        init_idt();
	print("initializing PICs...\n");
	init_pics(0x20, 0x28);
        print("initializing keyboard...\n");
        init_keyboard();
        print("enabling keyboard interrupts...\n");
        enable_irq(1);
        send_eoi(0);
        __asm__ __volatile__ ("sti");
	cprint("Hello OS\n", 2);
        //print_mboot_info(mbd);
	update_cursor();
        shell();
        exit();
}
void exit(void){
	while(inportb(0x64) & 0x02);
	outportb(0x64, 0xFE);
}
