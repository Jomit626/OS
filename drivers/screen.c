#include "screen.h"
#include "../kernel/uilts.h"
#include "ports.h"

#define VEDIO_MEMORY 0Xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Screen device I/O ports
#define REG_SCREEN_CTRL (u16)0x3D4
#define REG_SCREEN_DATA (u16)0x3D5
// get pos, NOT offset,offset = pos*2
#define GET_POS(ROW, COL) ((ROW)*80 + (COL))

//prvite func
void print_cur(char charactor, char color);
int get_cursor();
void set_cursor(int pos);
//--- Public func

void screen_init(){
    int i;

    for (i = 0; i < (MAX_COLS * MAX_ROWS);i+=2){
        char *videomem = (char *)(VEDIO_MEMORY + (char *)i);
        videomem[0] = '\0';
        videomem[1] = WHITE_ON_BLACK;

    }
    set_cursor(0);
}

void print_string(char* string){
    while(*string != '\0'){
        print_cur(*string, WHITE_ON_BLACK);
        string++;
    }
}

//--- Prvite func

void print_cur(char charactor,char color){
    int pos = get_cursor();
    // switch line
    if (charactor == '\n'){
        pos = GET_POS(pos / MAX_COLS + 1, 0);
    } else {
        print_char(pos, charactor, color);
        pos++;
    }

    
    // Roll the screen
    if (pos >= MAX_COLS*MAX_ROWS){
        int i;
        char *video_memory = (char *)(VEDIO_MEMORY);
        // rolling
        for (i = 1; i < MAX_ROWS;i++){
            memory_copy(video_memory + GET_POS(i, 0)*2,
                        video_memory + GET_POS(i - 1, 0)*2,
                        MAX_COLS * 4); //4 bytes a char and color
        }
        //make last row enpty
        for(video_memory += GET_POS(MAX_ROWS - 1, 0) * 2;video_memory < (char*)(VEDIO_MEMORY+GET_POS(MAX_ROWS,MAX_COLS)*2);video_memory+=2){
            video_memory[0] = 0x0;
            video_memory[1] = WHITE_ON_BLACK;
        }
        pos = GET_POS(MAX_ROWS-1, 0);
    }

    set_cursor(pos);
}

void print_char(int pos, char charactor, char color)
{
    char *video_memory = (char *)(VEDIO_MEMORY + pos*2);
    video_memory[0] = charactor;
    video_memory[1] = color;
}

//---cursor contral
void set_cursor(int pos)
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (pos >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (pos & 0xff));
}

int get_cursor()
{
    int pos;
    port_byte_out(REG_SCREEN_CTRL, 14);
    pos = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    pos += port_byte_in(REG_SCREEN_DATA);

    return pos;
}
