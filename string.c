#include "io.h"
#include "string.h"
volatile unsigned char *videoram = (unsigned char *)0xB8000;
volatile unsigned char *cursor = (unsigned char *)0xB8000;
int crow, ccol;
void update_cursor(){

	unsigned short position=(crow*80) + ccol;
	
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (unsigned char)(position&0xFF));
	
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (unsigned char)((position>>8)&0xFF));
}
void kclear() {
    cursor = videoram;
    for (int i=0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        cursor[0] = ' ';
        cursor[1] = 0x07;
        cursor += 2;
		crow = 0;
		ccol = 0;
		update_cursor();
    }
    cursor = videoram;
}
/*01 = darkblue 02 = green 03 = lightblue 04 = darkred 05 = darkpink 06 = orange 07 = lightgray 08 = darkgray 09 = purple 10 = babygreen 11 = lightred 12 = lightpink 13 = yellow 14 = white*/
void cprint(char * str, char col) {
	while (*str != 0) {
		if (*str == '\n'){
			int offset = cursor - videoram;
			int column = offset % (SCREEN_WIDTH * 2);
			cursor += (SCREEN_WIDTH * 2) - column;
			ccol += ((SCREEN_WIDTH * 2) - column)/2;
			update_cursor();
			scroll();
		}else{
			kputc(*str, col);
			ccol++;
			update_cursor();
		}
		str++;
	}
}

void print(char * str) {
	while (*str != 0) {
		if (*str == '\n'){
			int offset = cursor - videoram;
			int column = offset % (SCREEN_WIDTH * 2);
			cursor += (SCREEN_WIDTH * 2) - column;
			ccol += ((SCREEN_WIDTH * 2) - column)/2;
			update_cursor();
			scroll();
		}else{
			ccol++;
			update_cursor();
			kputc(*str, 0x07);
		}
		str++;
	}
}
		

void kputc(char c, char col) {

    cursor[0] = c;
    cursor[1] = col;
    cursor += 2;
    scroll();
}
void scroll(){
int i;
int offset = cursor - videoram;
      if(offset >= 160*25)          /* Are we off-screen ?          */
      {
         for(i = 0; i < 160*24; i++)    /* Scroll the screen up         */
         {
            videoram[i] = videoram[i+160];
         }
         for(i = 0; i < 80; i++)        /* Empty the bottom row         */
         {
            videoram[(160*24)+(i*2)] = 0x20;
            videoram[(160*24)+(i*2)+1] = 0x07;
         }
         cursor -= 160;             /* We're on the bottom row      */
      }
   }


int strcheck(char * str1, char * str2){
	while(*str1 == *str2 && *str1 != 0 && *str2 !=0) {str1++; str2++;}
	if(*str1 == *str2) return 1;
	return 0;
}
