#include "../kernel/uilts.h"
#include "../drivers/screen.h"

void game_init();
void game_print_border();
void game_create_snake();
void game_over();


void game_keyboard(u32 key);
void game_time_tick();

void snake_move_and_draw();
void creat_food();

int is_out(int x, int y);
int is_on_snake(int x, int y);

