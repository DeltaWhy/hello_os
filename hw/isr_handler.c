#include "isr.h"
#include "../string.h"
#include "pic.h"
#include "keyboard.h"
void isr_handler(registers_t regs)
{
    switch(regs.int_no) {
        case 32:
            // timer
            send_eoi(0);
            break;
        case 33:
            // keyboard
            keyboard_irq_handler();
            send_eoi(1);
            break;
        default:
            print("interrupt ");
            char int_no[12];
            print(itoa(regs.int_no, int_no, 10));
            print("\n");
            break;
    }
}
