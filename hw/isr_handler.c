#include "globals.h"
#include "isr.h"
#include "screen.h"
#include "pic.h"
#include "keyboard.h"
#include "pit.h"
void isr_handler(registers_t regs)
{
    switch(regs.int_no) {
        case 13:
            // GPF
            printf("general protection fault\n"
                    "error code: %#x %u\n"
                    "at %p\n", regs.err_code, regs.err_code, regs.eip);
            printf("register dump:\n"
                    "    eax=%#.8x\n"
                    "    ebx=%#.8x\n"
                    "    ecx=%#.8x\n"
                    "    edx=%#.8x\n"
                    "    esp=%#.8x\n"
                    "    ebp=%#.8x\n"
                    "    esi=%#.8x\n"
                    "    edi=%#.8x\n"
                    "    cs=%#x ds=%#x ss=%#x\n"
                    "    eflags=%#.8x\n",
                    regs.eax, regs.ebx, regs.ecx, regs.edx, regs.esp, regs.ebp,
                    regs.esi, regs.edi, regs.cs, regs.ds, regs.ss, regs.eflags);
            panic("CPU exception in kernel code");
            break;
        case 32:
            // timer
            for (int i=0;i<100;i++)  
                timer_callback(regs);  
            send_eoi(0);
            break;
        case 33:
            // keyboard
            keyboard_irq_handler();
            send_eoi(1);
            break;


        default:
            printf("interrupt %d\n", regs.int_no);
            break;
    }
}
