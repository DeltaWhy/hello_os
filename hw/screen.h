#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 26





void update_cursor();
void kclear();
void kputc(char c, char col);
void print(char * str);
void cprint(char * str, char col);
void charPrint(char str);
void scroll();
char * itoa( int value, char * str, int base );
extern volatile unsigned char *videoram;
extern volatile unsigned char *cursor;
extern int ccol;
extern int crow;
#endif
