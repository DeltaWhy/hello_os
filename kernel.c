#include <stdint.h>
#include "globals.h"
#include "string.h"
#include "mboot.h"
#include "hw/pic.h"
#include "hw/port.h"
#include "hw/keyboard.h"
#include "hw/screen.h"
#include "hw/idt.h"
#include "mem/gdt.h"
#include "shell/shell.h"
void exit(void);

void kmain(uint32_t magic) {
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
        print("initializing shell...\n");
        init_shell_builtins();
	cprint("Hello OS\n", 2);
	update_cursor();
        shell();
}
void exit(void){
	while(inportb(0x64) & 0x02);
	outportb(0x64, 0xFE);
}
