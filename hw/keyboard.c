#include "../globals.h"
#include "keyboard.h"
#include "port.h"
#include "screen.h"
#include "../string.h"
#include "../cbuf.h"
int led_stat=0;

#include "scancode.h"

static cbuf key_buf;
static cbuf line_buf;
static kbd_info keyboard;

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

    cbuf_new(&key_buf);
    cbuf_new(&line_buf);
    keyboard.mode = 0;
    keyboard.held = 0;
}

void keyboard_irq_handler() {
    // put scancode in buffer
    while (!(inportb(KBD_CONTROLLER_REG)&KBD_STATS_OUT_BUF));
    int scancode = inportb(0x60);
    if (keyboard.mode & KBD_INFO_MODE_RAW) {
        cbuf_push(&key_buf, scancode);
    }
    if (!(scancode & 0x80)) {
        char c = scancode_to_ascii[scancode];
        if (c && keyboard.mode & KBD_INFO_MODE_ECHO) {
            kputc(c, 0x07);
        }
        if (c && !(keyboard.mode & (KBD_INFO_MODE_RAW | KBD_INFO_MODE_LINE))) {
            // character mode
            cbuf_push(&key_buf, c);
        } else if (c && KBD_INFO_MODE_LINE) {
            if (c == '\n') {
                while (!cbuf_empty(&line_buf)) {
                    cbuf_push(&key_buf, cbuf_pop(&line_buf));
                }
                cbuf_push(&key_buf, '\n');
            } else {
                cbuf_push(&line_buf, c);
            }
        }
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

void kbd_set_mode(uint32_t mode) {
    // if switching raw/cooked mode, flush the buffer
    if ((mode & KBD_INFO_MODE_RAW) ^ (keyboard.mode & KBD_INFO_MODE_RAW)) cbuf_flush(&key_buf);
    // if switching out of line mode, consume the line buffer
    if ((keyboard.mode & KBD_INFO_MODE_LINE) && !(mode & KBD_INFO_MODE_LINE)) {
        while (!cbuf_empty(&line_buf)) {
            cbuf_push(&key_buf, cbuf_pop(&line_buf));
        }
    }
    keyboard.mode = mode;
}

char getchar(){
    while(cbuf_empty(&key_buf)) wait();
    return cbuf_pop(&key_buf);
}

char * kgets(char * buf) {
    char *p = buf;
    char c;
    while ((c = getchar()) != '\n') {
        *p = c;
        p++;
    }
    *p = '\0';
    return buf;
}
