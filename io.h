#ifndef HELLO_LIB_IO
#define HELLO_LIB_IO

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 26

void kclear();
void kputc(char c);
void kputs(char * str);
extern volatile unsigned char *videoram;
extern volatile unsigned char *cursor;

#endif
