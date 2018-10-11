
#define VEDIO_MEMORY 0XB8000
#define MAX_ROWS 80
#define MAX_COLS 25

#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports 
#define REG_SCREEN_CTRL 0x3D4u
#define REG_SCREEN_DATA 0x3D5u

void screen_init();
void print_string(char *string);
void print_char(char row, char col, char charactor , char color);
void print_cur(char charactor, char color);
void clean_screen(char color);
int get_cursor();
void set_cursor(int offset);