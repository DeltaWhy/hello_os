#include <stdint.h>
#include "io.h"
 
void kmain(void)
{
    extern uint32_t magic;

    /* Uncomment the following if you want to be able to access the multiboot header */
    /* extern void *mbd; */

    if ( magic != 0x2BADB002 )
    {
    	
    	print("Something went not according to specs.");

        /* Something went not according to specs. Print an error
         message and halt, but do *not* rely on the multiboot 
         data structure. */
    }

    /* You could either use multiboot.h */
    /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
    /* or do your offsets yourself. The following is merely an example. */ 
    //char * boot_loader_name =(char*) ((long*)mbd)[16];

    /* Print a letter to screen to see everything is working: */
    kclear();
    //char * hello = "Jonathan made a color print function and a newline one.\n";

	print("a\n");
	print("b\n");
	print("c\n");
	print("d\n");
	print("e\n");
	print("f\n");
	print("g\n");
	print("h\n");
	print("i\n");
	print("j\n");
	print("h\n");
	print("i\n");
	print("j\n");
	print("k\n");
	print("l\n");
	print("m\n");
	print("n\n");
	print("o\n");
	print("p\n");
	print("q\n");
	print("r\n");
	print("s\n");
	print("t\n");
	print("u\n");
	print("v\n");
	print("w\n");
	print("x\n");
	print("y\n");
	print("z\n");


}
