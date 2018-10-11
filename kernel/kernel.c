#include "kernel.h"
#include "../drivers/screen.c"

int main(void)
{
    int offset = get_cursor();
    print_char(11, 10 + offset, 'A', WHITE_ON_BLACK);
    screen_init();
    print_char(10, 10, 'A', WHITE_ON_BLACK);
    print_char(11, 10 + offset, 'A', WHITE_ON_BLACK);
    set_cursor(2);
    offset = get_cursor();
    print_char(12, 10 + offset, 'A', WHITE_ON_BLACK);
    print_string("Hello!");
}
