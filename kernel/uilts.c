#include "uilts.h"
#include "../drivers/screen.h"
// Mem copy ,can be faster
void memory_copy(char *source, char *dest, int nbytes)
{
    int i = 0;
    for (i = 0; i < nbytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}

void int_to_ascii(u32 i, char *str)
{
    char *str1 = str;
    u8 sign = 0;
    if (i < 0)
    {
        sign = 1;
        i = -i;
    }

    do
    {
        *str = '0' + i % 10;
        i /= 10;
        str++;
    } while (i);
    if (sign)
    {
        *str = '-';
    }

    *(str++) = '\0';
    str_reverse(str1);
}
void str_reverse(char *str)
{
    u32 i = 0, j = 0;
    while (str[i] != '\0')
        i++;
    i--;
    for (j = 0; j <= i / 2;j++){
        
        char c = str[j];
        str[j] = str[i - j];
        str[i - j] = c;
    }
}
void debug(){
    int i, j;
    for (i = 0, j = 0; i < 1e10;i++)
        j++;
}
void print_in_bit(u32 i){
    u32 mask = 1 << 31;
    while(mask){
        if (mask & i)
            print_string("1");
        else
            print_string("0");
        mask >>= 1;
    }
    print_string("end\n");
}