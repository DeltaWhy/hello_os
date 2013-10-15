#ifndef ISR_H
#define ISR_H
#include <stdint.h>
typedef struct registers
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;
extern void _isr_0();
extern void _isr_1();
extern void _isr_2();
extern void _isr_3();
extern void _isr_4();
extern void _isr_5();
extern void _isr_6();
extern void _isr_7();
extern void _isr_8();
extern void _isr_9();
extern void _isr_10();
extern void _isr_11();
extern void _isr_12();
extern void _isr_13();
extern void _isr_14();
extern void _isr_15();
extern void _isr_16();
extern void _isr_17();
extern void _isr_18();
extern void _isr_19();
extern void _isr_20();
extern void _isr_21();
extern void _isr_22();
extern void _isr_23();
extern void _isr_24();
extern void _isr_25();
extern void _isr_26();
extern void _isr_27();
extern void _isr_28();
extern void _isr_29();
extern void _isr_30();
extern void _isr_31();
#endif
