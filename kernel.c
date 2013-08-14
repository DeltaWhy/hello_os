#include <stdint.h>
#include "pic.h"
#include "io.h"
#include "keyboard.h"
#include "string.h"
#include "gdt.h"
void init_gdt(void);
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
	print("initializing PICs...\n");
	init_pics(0x20, 0x28);
	cprint("Jonathan's OS\n", 2);
	update_cursor();
	while(1){
		char * input = keyboard();
		if (strcheck(input, "help") == 1){
			print("supported commands:\nhelp - displays this message.\nclear - clears the screen.\nreboot - might make it restart.\n");
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
		else{
			print("don't know that one\n");
		}
	}
}
void exit(void){
	while(inportb(0x64) & 0x02);
	outportb(0x64, 0xFE);
}
void init_gdt(void) {
    /*GDT[0] = ((sizeof(gdt_descriptor) * GDT_ENTRIES - 1) & 0xFFFF)
            | ((uint32_t)GDT) << 16;*/
    GDT[1] = create_descriptor(0, 0xFFFFF, GDT_CODE_PL0);
    GDT[2] = create_descriptor(0, 0xFFFFF, GDT_DATA_PL0);
    setGdt(GDT, sizeof(GDT));
}
