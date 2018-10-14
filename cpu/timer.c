#include "timer.h"
#include "ISR.h"
#include "../drivers/ports.h"

//public
timer_event_t events[MAX_TIME_EVENT];
u32 event_num = 0;
void register_time_event(timer_event_t t){
    if (event_num < MAX_TIME_EVENT)
        events[event_num++] = t;
}

//private

void timer_handler(registers_t t);

void timer_init(u32 freq){

    u16 reload_value = (u16)(1193182 / freq);
    //we ues channal 0 only 
    port_byte_out(0x43, 0x36);//Access mode: lobyte/hibyte  Mode 3
    port_byte_out(0x40, reload_value & 0xff); 
    port_byte_out(0x40, (reload_value >> 8) & 0xff); //only even num!

    register_interrupt_handler(IRQ0, timer_handler);
}

void timer_handler(registers_t t){
    int i = 0;
    for (i = 0; i < event_num;i++)
        events[i]();
}