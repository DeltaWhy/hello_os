#include <stdbool.h>
#include "globals.h"
#include "shell.h"
#include "../hw/keyboard.h"
#include <string.h>
#include "../hw/screen.h"

static builtin builtins[MAX_BUILTINS];
static int num_builtins = 0;

void shell() {
    kbd_set_mode(KBD_INFO_MODE_ECHO | KBD_INFO_MODE_LINE);
    char input[1024];
    while(1) {
        cprint("> ", 0x0A);
        kgets(input);
        bool found = false;
        for (int i=0; i < num_builtins; i++) {
            if (strcmp(input, builtins[i].name) == 0) {
                found = true;
                (*(builtins[i].fn))(0, NULL);
                break;
            }
        }
        if (!found) {
            printf("%s: command not found", input);
        }
        continue;
    }
}

void register_builtin(builtin b) {
    builtins[num_builtins] = b;
    num_builtins++;
}

void help(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);
    print("supported commands:\n");
    for (int i=0; i < num_builtins; i++) {
        printf("    %s - %s\n", builtins[i].name, builtins[i].description);
    }
}
builtin help_builtin = {&help, "help", "Prints this message."};

void clear(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);
    kclear();
}
builtin clear_builtin = {&clear, "clear", "Clears the screen."};

void interrupt(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);
    print("interrupting...\n");
    __asm__ __volatile__ ("int $33");
}
builtin interrupt_builtin = {&interrupt, "interrupt", "Tests software interrupts."};

void crash(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);
    print("dividing by 0...\n");
    int x, y, z;
    x = 10;
    y = 0;
    z = x / y;
    x = z;
}
builtin crash_builtin = {&crash, "crash", "Tests CPU exception handling by dividing by 0."};

void test_panic(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);
    print("panicking...\n");
    panic("panic test");
    print("this should never print");
}
builtin panic_builtin = {&test_panic, "panic", "Tests kernel panic function."};

extern builtin bootinfo_builtin;

extern char *kernel_heap_start;
extern char *kernel_heap_end;
void heap(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);
    printf("kernel heap start: %p\n"
           "              end: %p\n", kernel_heap_start, kernel_heap_end);
}
builtin heap_builtin = {&heap, "heap", "Show size of the kernel heap."};

void init_shell_builtins() {
    register_builtin(help_builtin);
    register_builtin(clear_builtin);
    register_builtin(interrupt_builtin);
    register_builtin(crash_builtin);
    register_builtin(panic_builtin);
    register_builtin(bootinfo_builtin);
    register_builtin(heap_builtin);
}

