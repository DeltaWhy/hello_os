#include "shell.h"
#include "../hw/keyboard.h"
#include "../string.h"
#include "../hw/screen.h"

void shell() {
    kbd_set_mode(KBD_INFO_MODE_ECHO | KBD_INFO_MODE_LINE);
    char input[1024];
    while(1) {
        print("> ");
        kgets(input);
        if (strcmp(input, "help") == 0){
            print("supported commands:\nhelp - displays this message.\nclear - clears the screen.\nreboot - might make it restart.\ninterrupt - tests the interrupt system.\ncrash - attempts to divide by zero.\n");
        }
        else if (strcmp(input, "clear") ==0)
        {
            kclear();
        }
        else if (strcmp(input, "reboot") == 0)
        {
            return;
        }
        else if (strcmp(input, "interrupt") == 0)
        {
            print("interrupting...\n");
            __asm__ __volatile__ ("int $33");
        }
        else if (strcmp(input, "crash") == 0)
        {
            print("dividing by 0...\n");
            int x, y, z;
            x = 10;
            y = 0;
            z = x / y;
            x = z;
        }
        else{
            print(input);
            print(": command not found");
        }
    }
}
