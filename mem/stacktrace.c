#include <stdint.h>
#include "sprintf.h"
#include "mem/stacktrace.h"
#include "hw/screen.h"
#include "hw/port.h"
extern void * stack_top;
extern void * stack_bottom;

void stacktrace(void) {
    void **ebp;
    __asm__ ("movl %%ebp, %0"
            : "=a"(ebp));
    printf("call stack:\n");
    bochslog("call stack:\naddr2line -fspi -e kernel.elf ");
    while (ebp < &stack_top && ebp >= &stack_bottom) {
        char str[11];
        void *raddr = ebp[1];
        sprintf(str, "%p", raddr);
        printf("    %p\n", raddr);
        bochslog(str);
        bochslog(" ");
        ebp = ebp[0];
    }
    bochslog("\n");
}
