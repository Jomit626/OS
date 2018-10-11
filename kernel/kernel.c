int func(void){
    //func();
    char *video_memory = (char *)0xb8000; //for test
    *video_memory = 'D';
}

int main(void){
    func();
    char *video_memory = (char *)0xb8000; //for test
    *video_memory = 'A';
}