#ifndef _SCREEN
#define _SCREEN


#define WHITE_ON_BLACK 0x0f



// Public func 
void screen_init();
void print_string(char *string);
void print_char(int pos, char charactor , char color);


#endif