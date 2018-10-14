#include "kernel.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "uilts.h"
#include "../cpu/ISR.h"
#include "../cpu/timer.h"

int main(void)
{   
    ISR_install();
    screen_init();
    keyboard_init();
    timer_init(1);

    register_keyevent(game_keyboard);
    register_time_event(game_time_tick);
}

#define KEY_MASK(K) ( 1 << ((K)-0x61))


void game_time_tick(){
    
}

void game_keyboard(u32 key){
    if (key & KEY_MASK('w')){
        print_cur('w',0xf0);
    }
    if (key & KEY_MASK('a')) {
        print_cur('a',0xf0);
    }
    if (key & KEY_MASK('s')){
        print_cur('s',0xf0);
    }
    if (key & KEY_MASK('d')){
        print_cur('d',0xf0);
    }
}