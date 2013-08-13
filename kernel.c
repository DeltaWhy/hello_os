#include <stdint.h>
#include "pic.h"
#include "io.h"
#include "keyboard.h"
#include "string.h"
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
