#ifndef __KEYBOARD
#define __KEYBOARD
#include "../kernel/uilts.h"
#include "../cpu/ISR.h"

#define ACK 0xfa
#define RESEND 0xFE 
#define SELF_TESR_PASS 0xaa

//to save 32 keys' status
//0 - 25 a - z (1<<'a' - 0x61) lol
//
//

u32 get_key_status();
void keyborad_interrupt_hanlde(registers_t t);

//software keyboard event
#define MAX_KEY_T 256
typedef void (*kboard_t)(u32 KEY_status);
void register_keyevent(kboard_t t);

void keyboard_init();


#endif 