#ifndef _SCREEN
#define _SCREEN


#define WHITE_ON_BLACK 0x0f
#define VEDIO_MEMORY 0Xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// get pos, NOT offset,offset = pos*2
#define GET_POS(ROW, COL) ((ROW)*80 + (COL))

// Public func 
void screen_init();
void print_string(char *string);
void print_char(int pos, char charactor , char color);
void set_cursor(int pos);
void print_cur(char charactor, char color);
#endif