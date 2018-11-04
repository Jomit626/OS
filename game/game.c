#include "game.h"
#include "../drivers/screen.h"
#include "../kernel/uilts.h"
//random
double r_seed;
double rand0_1(double *r)
{
    double base=256.0;
    double a=17.0;
    double b=139.0;
    double temp1=a*(*r)+b;
    double temp2=(int)(temp1/base);
    double temp3=temp1-temp2*base;
    *r=temp3;
    double p=*r/base;
    return p;
}
//Game ststus,game starts = 1,game end = 2
u32 game_staus = 0;
u32 tick = 0;

//snake
#define MAX_LENGTH 1000
typedef struct
{
    int x; //row
    int y; //col
} vetor;

vetor snakes[MAX_LENGTH];
vetor snake_v, snake_v_last;
int snake_length = 0;
//food
vetor food;

// image
#define BG '\0'
#define BG_COR 0x0f
#define BORDER '\0'
#define BORDER_COR 0xf0
#define SNAKE '\0'
#define SNAKE_COR 0xa0
#define FOOD '\0'
#define FOOD_COR 0x40
#define MAX_ROWS_GAME 20
#define MAX_COLS_GAME 20

#define KEY_MASK(K) (1 << ((K)-0x61))

void game_init()
{
    screen_init();
    set_cursor(-1); //disable cur
    game_print_border();
    snake_length = 0;
    game_create_snake();
    creat_food();
    tick = 0;
    game_staus = 0; //game_wait_for_start
}

void game_time_tick()
{

    tick++;
    if (tick >= 10){
    tick = 0;
    if (game_staus == 1)
    {
        
        snake_move_and_draw();
    }
    }
}

void game_over()
{
    game_staus = 2;
    set_cursor(0);
    print_char(GET_POS(food.x, food.y), BG, BG_COR);
    print_string("GAME OVER");
    game_init();
}

void game_keyboard(u32 key)
{
    if (game_staus == 1)
    { //game starts
        if (key & KEY_MASK('w'))
        {
            snake_v.x = -1;
            snake_v.y = 0;
        }
        else if (key & KEY_MASK('a'))
        {
            snake_v.x = 0;
            snake_v.y = -1;
        }
        else if (key & KEY_MASK('s'))
        {
            snake_v.x = 1;
            snake_v.y = 0;
        }
        else if (key & KEY_MASK('d'))
        {
            snake_v.x = 0;
            snake_v.y = 1;
        }
        //to avoid snake go back
        if ((snake_v.x + snake_v_last.x) == 0 && 
            (snake_v.y + snake_v_last.y) == 0){
                snake_v.x = snake_v_last.x;
                snake_v.y = snake_v_last.y;
        }
    }
    else if (game_staus == 0)
    {
        if (key & (KEY_MASK('d') | KEY_MASK('s') | KEY_MASK('a') | KEY_MASK('w'))){
            
            if (key & KEY_MASK('w'))
            {
                r_seed = 1234;
                snake_v.x = -1;
                snake_v.y = 0;
            }
            else if (key & KEY_MASK('a'))
            {
                r_seed = 92394;
                snake_v.x = 0;
                snake_v.y = -1;
            }
            else if (key & KEY_MASK('s'))
            {
                r_seed = 3431;
                snake_v.x = 1;
                snake_v.y = 0;
            }
            else if (key & KEY_MASK('d'))
            {
                r_seed = 34523;
                snake_v.x = 0;
                snake_v.y = 1;
            }
            
            game_staus = 1;
        }
    }
}

void game_print_border()
{
    int row = 0, col = 0;
    for (col = 0; col < MAX_COLS_GAME; col++)
    {
        print_char(GET_POS(0, col), BORDER, BORDER_COR);
    }
    for (row = 0; row < MAX_ROWS_GAME; row++)
    {
        print_char(GET_POS(row, MAX_COLS_GAME - 1), BORDER, BORDER_COR);
    }
    for (col = MAX_COLS_GAME - 1; col >= 0; col--)
    {
        print_char(GET_POS(MAX_ROWS_GAME - 1, col), BORDER, BORDER_COR);
    }
    for (row = MAX_ROWS_GAME - 1; row >= 0; row--)
    {
        print_char(GET_POS(row, 0), BORDER, BORDER_COR);
    }
}

void game_create_snake()
{
    snake_length = 2;
    snakes[0].x = 5;
    snakes[0].y = 5;
    snakes[1].x = 5;
    snakes[1].y = 5;
    //first print
    print_char(GET_POS(snakes[0].x,
                       snakes[0].y),
               SNAKE, SNAKE_COR);
    print_char(GET_POS(snakes[1].x,
                       snakes[1].y),
               SNAKE, SNAKE_COR);
    snake_v.x = 0;
    snake_v.y = 0;
    snake_v_last.x = 0;
    snake_v_last.x = 0;
}

//snake contral
void snake_move_and_draw()
{
    //record its last move
    snake_v_last.x = snake_v.x;
    snake_v_last.y = snake_v.y;
    //record tail's pos
    int x = snakes[snake_length - 1].x;
    int y = snakes[snake_length - 1].y;
    //make every part of snake move forward
    int i;
    for (i = 1; i < snake_length ; i++)
    {
        snakes[snake_length - i].x = snakes[snake_length - i - 1].x;
        snakes[snake_length - i].y = snakes[snake_length - i - 1].y;
    }
    //make head move forward
    snakes[0].x += snake_v.x;
    snakes[0].y += snake_v.y;

    print_char(GET_POS(snakes[0].x,
                       snakes[0].y),
               SNAKE, SNAKE_COR);
    
    //to test if the snake can eat food
    if (snakes[0].x == food.x && snakes[0].y == food.y)
    {
        snakes[snake_length].x = x;
        snakes[snake_length].y = y;
        snake_length++;
        //make new food
        creat_food(); //TODO-------
    } else {//remove the tail
        print_char(GET_POS(x, y), BG, BG_COR);
    }
    //out of border?
    //print new head and clear old tail
    if (is_out(snakes[0].x, snakes[0].y))
        game_over();
    //touch self?
    for (i = 1; i < snake_length; i++)
    {
        if (snakes[0].x == snakes[i].x && snakes[0].y == snakes[i].y)
            game_over();
    }
}

//food
void creat_food()
{
    do{
        food.x = MAX_ROWS_GAME * rand0_1(&r_seed);
        food.y = MAX_COLS_GAME * rand0_1(&r_seed);

    } while (is_out(food.x, food.y) || is_on_snake(food.x, food.y));
    print_char(GET_POS(food.x,
                       food.y),
               FOOD, FOOD_COR);
}

int is_out(int x, int y)
{
    return !((y > 0) && (y < MAX_COLS_GAME - 1) && (x > 0) && (x < MAX_ROWS_GAME - 1));
}
int is_on_snake(int x, int y){
    int i;
    for (i = 1; i < snake_length; i++)
    {
        if (x == snakes[i].x && y == snakes[i].y)
            return 1;
    }
    return 0;
}