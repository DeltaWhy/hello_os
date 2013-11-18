#include "port.h"
#include "screen.h"
#include "../string.h"
#include "isr.h"
#include "../globals.h"
#include "pit.h"
unsigned long counter = 0;

void init_speaker(int hz)
{
    int divisor = 1193180 / hz;
    outportb(PIT_CMDREG, 0xb6);
    outportb(PIT_CHANNEL2, (unsigned char) (divisor) );
    outportb(PIT_CHANNEL2, (unsigned char) (divisor >> 8));	
}

void init_timer(int hz)
{
    int divisor = 1193180 / hz;       
    outportb(PIT_CMDREG , 0x36);             
    outportb(PIT_CHANNEL0, divisor & 0xFF);   
    outportb(PIT_CHANNEL0, divisor >> 8);  
}


void timer_handler(registers_t regs)
{
	UNUSED(regs);
	printf("%x\n",counter);
	counter++;
}

void delay(int count)
{
      unsigned long wait_till;//This is addition of count and the current no of ticks

      wait_till = counter + count;
	printf("%d\n",counter);
      while(counter < wait_till);//loops until the given period has been reached
}


void beep(unsigned int wait_time,unsigned int times ) 
{
	UNUSED(wait_time);
     unsigned char tempA = inportb(0x61);
     unsigned char tempB = (inportb(0x61) & 0xFC);
     unsigned int count;
	
    for(count =0;count == times;count++) 
    {
         if (tempA != (tempA | 3)) 
         {
              outportb(0x61, tempA | 3);
         }
        //delay(wait_time);
        outportb(0x61, tempB);
   }
}
