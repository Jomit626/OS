#ifndef __TIMER
#define __TIMER
#include "../kernel/uilts.h"

void timer_init(u32 freq);

//software timer event
#define MAX_TIME_EVENT 256
typedef void (*timer_event_t)();

void register_time_event(timer_event_t t);

#endif