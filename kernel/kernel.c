#include "kernel.h"
#include "../drivers/screen.h"

int main(void)
{
    screen_init();
    int i,j,k=0;
    for (i = 0; i < 20*25;i++){
        for (j = 0; j < 1e5;j++)
            k++;
        print_string("1234");
    }
    print_string("12345");
    
}
