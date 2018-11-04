#include "kernel.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/ISR.h"
#include "../cpu/timer.h"
#include "../game/game.h"

int main(void)
{   
    ISR_install();
    screen_init();
    keyboard_init();
    timer_init(1);

    register_keyevent(game_keyboard);
    register_time_event(game_time_tick);

    game_init();
}

