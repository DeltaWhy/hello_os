#include "isr.h"
#include "../string.h"
void isr_handler(registers_t regs)
{
    print("interrupt ");
    char int_no[12];
    print(itoa(regs.int_no, int_no, 10));
    print("\n");
}
