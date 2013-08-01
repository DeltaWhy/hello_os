#include "inout.h"
#include "io.h"
char keysq[100];
int kcount;
int kcheck;
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
void keyboard(){
	int code;
	outportb(0x60, 0xF4);
	back:
	code = scan();
	if (code == 0x01){
		print("esc");

	}
	else if (code == 0x02){
		print("1");

		
	}
	else
		goto back;
	
}
