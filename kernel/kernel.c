#include "kernel.h"
#include "../drivers/screen.h"
#include "uilts.h"
#include "../cpu/ISR.h"

int main(void)
{   
    ISR_install();
    screen_init();
}
