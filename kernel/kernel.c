#include "kernel.h"
#include "../drivers/screen.h"

int main(void)
{
    screen_init();
    int i = 0;
    print_string("Hello11111!\n");
    for (i = 0; i < 21;i++){
        print_string("Hello!\n");
    }
        
}
