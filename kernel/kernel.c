#include "kernel.h"
#include "../drivers/screen.h"
#include "uilts.h"
#include "../cpu/ISR.h"
#include "../cpu/IDT.h"
#include "../cpu/ISR.h"

int main(void)
{   
    ISR_install();
    //PIC_remap(0x20,0x28);

    //screen_init();
    char a[10] = "Hello!";
    print_string(a);
    //print_string("END");
    __asm__ __volatile__("int $6");
    


    //print_string("A");
}
