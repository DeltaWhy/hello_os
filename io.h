#ifndef HELLO_LIB_IO
#define HELLO_LIB_IO

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 26

void kclear();
void kputc(char c, char col);
void print(char * str);
void cprint(char * str, char col);
void scroll();
extern volatile unsigned char *videoram;
extern volatile unsigned char *cursor;
extern int off_screen;
#endif
