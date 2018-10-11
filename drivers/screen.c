#include "screen.h"
#include "../kernel/kernel_low_c.c"

void screen_init(){
    clean_screen(WHITE_ON_BLACK);
    set_cursor(0);
}

void print_char(char row, char col, char charactor, char color)
{
    char *video_memory = (char *)(VEDIO_MEMORY + 2 * (MAX_ROWS * row + col));
    *video_memory = charactor;
    *(video_memory + 1) = color;
}

void print_cur(char charactor, char color){
    int offset = get_cursor();
    if (charactor=='\n'){
        set_cursor((offset / 160 + 1)* MAX_ROWS * 2);
        return;
    }
    char *video_memory = (char *)(VEDIO_MEMORY + offset);
    *video_memory = charactor;
    *(video_memory + 1) = color;
    set_cursor(offset + 2);
    return;
}

void print_string(char* string){
    while((*string) != '\0'){
        print_cur(*string,WHITE_ON_BLACK);
        string += 1;
    }
}

void clean_screen(char color){
    int i = 0;
    char *video_memory = (char *)(VEDIO_MEMORY + 1);
    for (i = 0; i <= (MAX_COLS * MAX_ROWS); i++){
        *video_memory = 0x0;
        *(video_memory + 1) = color;
        video_memory += 2;
    }
    return;
}

int get_cursor() { 
    // The device uses its control register as an index
    // to select its internal registers , of which we are 
    // interested in:
    // reg 14: which is the high byte of the cursor’s offset 
    // reg 15: which is the low byte of the cursor’s offset 
    // Once the internal register has been selected , we may read or
    // write a byte on the data register. 
    port_byte_out(REG_SCREEN_CTRL , 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL , 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    // Since the cursor offset reported by the VGA hardware is the 
    // number of characters , we multiply by two to convert it to 
    // a character cell offset.
    return offset*2;
}

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL , 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset>>8)) ;
    port_byte_out(REG_SCREEN_CTRL,15 );
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}
