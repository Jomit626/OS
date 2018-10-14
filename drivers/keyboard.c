#include "keyboard.h"
#include "../drivers/screen.h"

u32 KEY_status = 0;
kboard_t key_event_r[MAX_KEY_T];
u32 key_event_c = 0;

//private func
u32 sent_byet(u8 com, u8 data, u8 testcode);
u8 codebyte_to_alphabet(u8 code);

void keyboard_init(){
    register_interrupt_handler(IRQ1, keyborad_interrupt_hanlde);
    //                                       Set scan code set 2             Set typematic rate and delay
    sent_byet(0xFF, 0, SELF_TESR_PASS);
    sent_byet(0xf5, 0, ACK);
    sent_byet(0xf0, 2, ACK);
    sent_byet(0xf3, 0, ACK);
    sent_byet(0xf4, 0, ACK);
    
}
u32 get_key_status(){
    return KEY_status;
}

//software keyboard event

void register_keyevent(kboard_t t){
    if (key_event_c < MAX_KEY_T){
        key_event_r[key_event_c++] = t;
    }
}

//------------------------------------------------------
u32 sent_byet(u8 com, u8 data,u8 testcode){
    int i;
    for (i = 0; i < 3;i++){
        port_byte_out(com, data);
        io_wait();
        u8 re = port_byte_in(com);
        if (re == testcode)
            return 1;
    }
    return 0;
}
void keyborad_interrupt_hanlde(registers_t t){

    u8 press = 1;
    u8 scancode = port_byte_in(0x60);
    if (scancode > 0x80){
        press = 0;
        scancode -= 0x80;
    }
    u8 c = codebyte_to_alphabet(scancode);

    if (c){
    if  (press)
        KEY_status |= 1 << (c-0x61);
    else 
        KEY_status &= ~(1 << (c-0x61));
    }
    u32 i;
    for (i = 0; i < key_event_c;i++)
            key_event_r[i](KEY_status);
}

u8 codebyte_to_alphabet(u8 code){
    
    switch (code)
    {
        case 0x1E: 
            return 'a';
        case 0x30: 
            return 'b';
        case 0x2E: 
            return 'c';
        case 0x20: 
            return 'd';
        case 0x12: 
            return 'e';
        case 0x21: 
            return 'f';
        case 0x22: 
            return 'g';
        case 0x23: 
            return 'h';
        case 0x17: 
            return 'i';
        case 0x24: 
            return 'j';
        case 0x25: 
            return 'k';
        case 0x26: 
            return 'l';
        case 0x32: 
            return 'm';
        case 0x31: 
            return 'n';
        case 0x18: 
            return 'o';
        case 0x19: 
            return 'p';
        case 0x10: 
            return 'q';
        case 0x13: 
            return 'r';
        case 0x1F: 
            return 's';
        case 0x14: 
            return 't';
        case 0x16: 
            return 'u';
        case 0x2F: 
            return 'v';
        case 0x11: 
            return 'w';
        case 0x2D: 
            return 'x';
        case 0x15: 
            return 'y';
        case 0x2C: 
            return 'z';

        default:
            return 0;
            break;
    }
}