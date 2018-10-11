#include "kernel.h"
#include "../drivers/screen.c"

int main(void)
{
    screen_init();
    print_string("Hello!\n");
    print_string("Hello!\n");
    print_string("Hello!\n");
}
