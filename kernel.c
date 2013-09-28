#include <stdint.h>
#include <string.h>
#include "pic.h"
#include "io.h"
#include "keyboard.h"
#include "string.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
void init_gdt(void);
void init_idt(void);
void exit(void);
void _interrupt_handler(void);
void set_idt_descriptor(int irq, void *handler, uint16_t selector, uint8_t type_attr);

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
	cprint("Jonathan's OS\n", 2);
	update_cursor();
	while(1){
            print("> ");
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
                else if (strcheck(input, "interrupt") == 1)
                {
                    print("interrupting...\n");
                    __asm__ __volatile__ ("int $0x1");
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
void init_gdt(void) {
    /*GDT[0] = ((sizeof(gdt_descriptor) * GDT_ENTRIES - 1) & 0xFFFF)
            | ((uint32_t)GDT) << 16;*/
    GDT[1] = create_descriptor(0, 0xFFFFF, GDT_CODE_PL0);
    GDT[2] = create_descriptor(0, 0xFFFFF, GDT_DATA_PL0);
    setGdt(GDT, sizeof(GDT));
}
void init_idt(void) {
    for (unsigned int i = 0; i < sizeof(IDT); i++) {
        *(((char *)IDT)+i) = 0;
    }
    set_idt_descriptor(0, _isr_1, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(1, _isr_1, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(2, _isr_2, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(3, _isr_3, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(4, _isr_4, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(5, _isr_5, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(6, _isr_6, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(7, _isr_7, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(8, _isr_8, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(9, _isr_9, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(10, _isr_10, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(11, _isr_11, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(12, _isr_12, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(13, _isr_13, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(14, _isr_14, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(15, _isr_15, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(16, _isr_16, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(17, _isr_17, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(18, _isr_18, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(19, _isr_19, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(20, _isr_20, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(21, _isr_21, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(22, _isr_22, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(23, _isr_23, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(24, _isr_24, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(25, _isr_25, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(26, _isr_26, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(27, _isr_27, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(28, _isr_28, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(29, _isr_29, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(30, _isr_30, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    set_idt_descriptor(31, _isr_31, 0x08, IDT_DPL0 | IDT_INT_32 | IDT_PRESENT);
    setIdt(IDT, sizeof(IDT));
}
void _interrupt_handler(void) {
    print("interrupt");
}
void isr_handler(registers_t regs)
{
    print("interrupt ");
    char int_no[12];
    print(itoa(regs.int_no, int_no, 10));
    print("\n");
}

void set_idt_descriptor(int irq, void *handler, uint16_t selector, uint8_t type_attr) {
    IDT[irq].offset_1 = ((uint32_t)handler) & 0xFFFF;
    IDT[irq].offset_2 = ((uint32_t)handler) >> 16;
    IDT[irq].selector = selector;
    IDT[irq].type_attr = type_attr;
}
