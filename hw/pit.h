#ifndef PIT_H
#define PIT_H
#include "isr.h"

void init_timer(unsigned long frequency);
void timer_callback(registers_t regs);
#endif
