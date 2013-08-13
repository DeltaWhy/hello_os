
#include "io.h"
#include "string.h"
int ccol;
int led_stat=0;
int crow;
char keysq[100];
int scan(){
	char oldkey;
	char key;
	for (;;){
		oldkey=key;
		key=inportb(0x60);
		if(!(oldkey==key)){
			return key;
		}
	}
}


void klights(){
	if (led_stat == 0){
		outportb(0x60, 0xED);
		while(inportb(0x64) & 2);
		outportb(0x60, 4);
		while(inportb(0x64) & 2);
		led_stat++;
	}
	else if (led_stat == 1){
		outportb(0x60, 0xED);
		while(inportb(0x64) & 2);
		outportb(0x60, 0);
		while(inportb(0x64) & 2);
		led_stat=0;
	}
}
char * keyboard(){
	for(int i=0;i<100;i++)
		keysq[i] = 0;
	int kcount = 0;
	int code = 0;
	scan(); //so it doesn't think its enter
	outportb(0x60, 0xF4);
	while (1){
		code = scan();
		if (code == 0x01){
			print("esc");
			kcount+=3;
		}
		else if (code == 0x02){
			print("1");
			keysq[kcount]='1';
			kcount++;
		
		}
		else if (code == 0x03){
			print("2");
			keysq[kcount]='2';
			kcount++;
		}
		else if (code == 0x04){
			print("3");
			keysq[kcount]='3';
			kcount++;
		}
		else if (code == 0x05){
			print("4");
			keysq[kcount]='4';
			kcount++;
		}
		else if (code == 0x06){
			print("5");
			keysq[kcount]='5';
			kcount++;
		}
		else if (code == 0x07){
			print("6");
			keysq[kcount]='6';
			kcount++;
		}
		else if (code == 0x08){
			print("7");
			keysq[kcount]='7';
			kcount++;
		}
		else if (code == 0x09){
			print("8");
			keysq[kcount]='8';
			kcount++;
		}
		else if (code == 0x0A){
			print("9");
			keysq[kcount]='9';
			kcount++;
		}
		else if (code == 0x0B){
			print("0");
			keysq[kcount]='0';
			kcount++;
		}
		else if (code == 0x0C){
			print("-");
			keysq[kcount]='-';
			kcount++;
		}
		else if (code == 0x0D){
			print("=");
			keysq[kcount]='=';
			kcount++;
		}
		else if (code == 0x0E){
			if (kcount > 0){
				ccol-=2;
				cursor-=2;
				print(" ");
				cursor-=2;//                    BKSP
				kcount--;
				keysq[kcount]=0;
			}
		}
		else if (code == 0x0F){
			print("    ");
		}
		else if (code == 0x10){
			print("q");
			keysq[kcount]='q';
			kcount++;
		}
		else if (code == 0x11){
			print("w");
			keysq[kcount]='w';
			kcount++;
	
		}
		else if (code == 0x12){
			print("e");
			keysq[kcount]='e';
			kcount++;
		}
		else if (code == 0x13){
			print("r");
			keysq[kcount]='r';
			kcount++;
		}
		else if (code == 0x14){
			print("t");
			keysq[kcount]='t';
			kcount++;
		}
		else if (code == 0x15){
			print("y");
			keysq[kcount]='y';
			kcount++;
		}
		else if (code == 0x16){
			print("u");
			keysq[kcount]='u';
			kcount++;
		}
		else if (code == 0x17){
			print("i");
			keysq[kcount]='i';
			kcount++;
		}
		else if (code == 0x18){
			print("o");
			keysq[kcount]='o';
			kcount++;
		}
		else if (code == 0x19){
			print("p");
			keysq[kcount]='p';
			kcount++;
		}
		else if (code == 0x1A){
			print("[");
			keysq[kcount]='[';
			kcount++;
		}
		else if (code == 0x1B){
			print("]");
			keysq[kcount]=']';
			kcount++;
		}
		else if (code == 0x1C){
							//				ENTER
			code = 0;
			print("\n");
			break;
		}
		else if (code == 0x1D){
			print("lctrl");
			kcount+=5;
		}
		else if (code == 0x1E){
			print("a");
			keysq[kcount]='a';
			kcount++;
		}
		else if (code == 0x1F){
			print("s");
			keysq[kcount]='s';
			kcount++;
		}
		else if (code == 0x20){
			print("d");
			keysq[kcount]='d';
			kcount++;
		}
		else if (code == 0x21){
			print("f");
			keysq[kcount]='f';
			kcount++;
		}
		else if (code == 0x22){
			print("g");
			keysq[kcount]='g';
			kcount++;
		}
		else if (code == 0x23){
			print("h");
			keysq[kcount]='h';
			kcount++;
		}
		else if (code == 0x24){
			print("j");
			keysq[kcount]='j';
			kcount++;
		}
		else if (code == 0x25){
			print("k");
			keysq[kcount]='[';
			kcount++;
		}
		else if (code == 0x26){
			print("l");
			keysq[kcount]='l';
			kcount++;
		}
		else if (code == 0x27){
			print(";");
			keysq[kcount]=';';
			kcount++;
		}
		else if (code == 0x28){
			print("'");
			keysq[kcount]='\'';
			kcount++;
		}
		else if (code == 0x29){
			print("`");
			keysq[kcount]='`';
			kcount++;
		}
		else if (code == 0x2A){
			print("lshift");
			kcount+=6;
		}
		else if (code == 0x2B){
			print("\\");
			kcount++;
		}
		else if (code == 0x2C){
			print("z");
			keysq[kcount]='z';
			kcount++;
		}
		else if (code == 0x2D){
			print("x");
			keysq[kcount]='x';
			kcount++;
		}
		else if (code == 0x2E){
			print("c");
			keysq[kcount]='c';
			kcount++;
		}
		else if (code == 0x2F){
			print("v");
			keysq[kcount]='v';
			kcount++;
		}
		else if (code == 0x30){
			print("b");
			keysq[kcount]='b';
			kcount++;
		}
		else if (code == 0x31){
			print("n");
			keysq[kcount]='n';
			kcount++;
		}
		else if (code == 0x32){
			print("m");
			keysq[kcount]='m';
			kcount++;
		}
		else if (code == 0x33){
			print(",");
			keysq[kcount]=',';
			kcount++;
		}
		else if (code == 0x34){
			print(".");
			keysq[kcount]='.';
			kcount++;
		}
		else if (code == 0x35){
			print("/");
			keysq[kcount]='/';
			kcount++;
		}
		else if (code == 0x36){
			print("rshift");
			kcount+=6;
		}
		else if (code == 0x38){
			print("lalt");
			kcount+=4;
		}
		else if (code == 0x39){
			print(" ");
			kcount++;
		}
		else if (code == 0x3A){
			klights();
		}	
	}
	return keysq;
}
