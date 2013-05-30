#include "io.h"
volatile unsigned char *videoram = (unsigned char *)0xB8000;
volatile unsigned char *cursor = (unsigned char *)0xB8000;

void kclear() {
    cursor = videoram;
    for (int i=0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        cursor[0] = ' ';
        cursor[1] = 0x07;
        cursor += 2;
    }
    cursor = videoram;
}

void kputs(char * str) {
    while (*str != 0) {
        kputc(*str);
        str++;
    }
}

void kputc(char c) {
    cursor[0] = c;
    cursor[1] = 0x07;
    cursor += 2;
}
