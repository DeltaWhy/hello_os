#include "hw/port.h"
#include "hw/screen.h"
#include "string.h"
#include "isr.h"
#include "globals.h"
unsigned long tick = 0;

void timer_callback(registers_t regs)
{
   UNUSED(regs);
   tick++;
   printf("Tick:%x \n",tick);
   
}

void init_timer(unsigned long frequency)
{
   // Firstly, register our timer callback.
   //register_interrupt_handler(IRQ0, &timer_callback);
//we don't have this feature
   // The value we send to the PIT is the value to divide it's input clock
   // (1193180 Hz) by, to get our required frequency. Important to note is
   // that the divisor must be small enough to fit into 16-bits.
   unsigned long divisor = 1193180 / frequency;

   // Send the command byte.
   outportb(0x43, 0x36);

   // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
   unsigned short l = (unsigned short)(divisor & 0xFF);
   unsigned short h = (unsigned short)( (divisor>>8) & 0xFF );

   // Send the frequency divisor.
   outportb(0x40, l);
   outportb(0x40, h);
} 
