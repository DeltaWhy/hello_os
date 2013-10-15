#include <stdint.h>
#include <string.h>
#include "hw/pic.h"
#include "hw/port.h"
#include "hw/keyboard.h"
#include "string.h"
#include "hw/idt.h"
#include "mem/gdt.h"
void exit(void);

void kmain(void)
{
    extern uint32_t magic;
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
	cprint("Jonathan's OS\n", 2);
	update_cursor();
        while(1); // the command prompt below stops keyboard interrupts from working
	while(1){
            print("> ");
		char * input = getln();
		if (strcheck(input, "help") == 1){
			print("supported commands:\nhelp - displays this message.\nclear - clears the screen.\nreboot - might make it restart.\ninterrupt - tests the interrupt system.\ncrash - attempts to divide by zero.\n");
		}
		else if (strcheck(input, "clear") ==1)
		{
			kclear();
		}
		else if (strcheck(input, "reboot") == 1)
		{
			exit();
			print("this needs to be fixed.  BAD.");
		}
                else if (strcheck(input, "interrupt") == 1)
                {
                    print("interrupting...\n");
                    __asm__ __volatile__ ("int $33");
                }
                else if (strcheck(input, "crash") == 1)
                {
                    print("dividing by 0...\n");
                    int x, y, z;
                    x = 10;
                    y = 0;
                    z = x / y;
                    x = z;
                }
		else{
			print("don't know that one\n");
		}
	}
}
void exit(void){
	while(inportb(0x64) & 0x02);
	outportb(0x64, 0xFE);
}
