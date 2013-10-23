#include "keyboard.h"
#include "port.h"
#include "screen.h"
int led_stat=0;

#include "scancode.h"

void init_keyboard() {
    // I have no idea if this is correct
    outportb(KBD_CONTROLLER_REG, KBD_CTL_CMD_READ_CMD);
    char cmd = inportb(KBD_CONTROLLER_REG);

    print("keyboard command byte: 0x");
    char cmdStr[3];
    itoa(cmd, cmdStr, 16);
    print(cmdStr);
    print("\n");
    outportb(KBD_CONTROLLER_REG, KBD_CTL_CMD_WRITE_CMD);
    outportb(KBD_CONTROLLER_REG, cmd | KBD_CMD_KEYBOARD_INTERRUPT);
}

void keyboard_irq_handler() {
	charPrint(getchar()); 
	//print("\n");

    inportb(0x60);
    int i = inportb(0x61);	//WEEP WEEP! MAGIC NUMBERS!
    outportb(0x61, i|0x80);
    outportb(0x61, i);
}



void klights(){
	if (led_stat == 0){
		outportb(KBD_ENCODER_REG, KBD_ENC_CMD_SET_LED);
		while(inportb(KBD_CONTROLLER_REG) & KBD_STATS_IN_BUF);
		outportb(KBD_ENCODER_REG, KBD_LED_CAPS);
		while(inportb(KBD_CONTROLLER_REG) & KBD_STATS_IN_BUF);
		led_stat++;
	}
	else if (led_stat == 1){
		outportb(KBD_ENCODER_REG, KBD_ENC_CMD_SET_LED);
		while(inportb(KBD_CONTROLLER_REG) & KBD_STATS_IN_BUF);
		outportb(KBD_ENCODER_REG, 0);
		while(inportb(KBD_CONTROLLER_REG) & KBD_STATS_IN_BUF);
		led_stat=0;
	}
}
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
char getchar(){
	char key;	

	outportb(KBD_ENCODER_REG, KBD_ENC_CMD_ENABLE);

	
                // wait for input

      //         while(!(inportb(KBD_CONTROLLER_REG)&KBD_STATS_OUT_BUF)){
	//	code = inportb(KBD_ENCODER_REG);
	//					
	//	}
	
                int scancode = scan();
		 key = scancode_to_ascii[scancode&0x7f];
		

		
		
		return key;
		

		
	
	return key;
}
