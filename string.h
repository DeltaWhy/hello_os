#ifndef STRING_H
#define STRING_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 26





void update_cursor();
void kclear();
void kputc(char c, char col);
void print(char * str);
void cprint(char * str, char col);
void scroll();
int strcheck(char *, char *);
extern volatile unsigned char *videoram;
extern volatile unsigned char *cursor;
extern int ccol;
extern int crow;
#endif
