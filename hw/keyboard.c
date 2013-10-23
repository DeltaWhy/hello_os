#include "keyboard.h"
#include "port.h"
#include "screen.h"
#include "../string.h"
#include "../cbuf.h"
int led_stat=0;

#include "scancode.h"

cbuf scan_buf;
kbd_info keyboard;

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

    cbuf_new(&scan_buf);
    keyboard.mode = 0;
    keyboard.held = 0;
}

void keyboard_irq_handler() {
    // put scancode in buffer
    while (!(inportb(KBD_CONTROLLER_REG)&KBD_STATS_OUT_BUF));
    char scancode = inportb(0x60);
    cbuf_push(&scan_buf, scancode);
    if (keyboard.mode & KBD_INFO_MODE_ECHO && !(scancode & 0x80)) {
        kputc(scancode_to_ascii[(size_t)scancode], 0x07);
    }

    // reset the keyboard
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

char getchar(){
    char c = 0;
    while (c == 0) {
        while (cbuf_empty(&scan_buf)) __asm__ ("hlt");
        int scancode = cbuf_pop(&scan_buf);
        if (scancode == 0xE0) {
            // special key - ignore for now
            while (cbuf_empty(&scan_buf)) __asm__ ("hlt");
            cbuf_pop(&scan_buf);
            continue;
        } else {
            c = scancode_to_ascii[scancode];
        }
    }
    return c;
}
