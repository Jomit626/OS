void print_block(int row,int col,char color);

int main(void){
    int i = 0;
    int j = 0;
    print_block(10, 10,0xf0);
    for (i = 0; i <= 25;i++){
        for (j = 0; j <= 80;j++)
            print_block(i, j,0xf0);
    }
}

void print_block(int row,int col,char color) {
    char *video_memory = (char *)(0xb8000+ 2*(80*row + col));
    *video_memory = '\0';
    *(video_memory-1) = color;
}