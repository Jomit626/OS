#include "kernel.h"
#include "../drivers/screen.h"
#include "uilts.h"
#include "../cpu/ISR.h"
#include "../cpu/IDT.h"

int main(void)
{
    screen_init();
    ISR_install();
    __asm__ __volatile__("int $1");
}
