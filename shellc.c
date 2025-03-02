#include <stdio.h>
#define BUF_SIZE 1024

char* shl_read_line(void){
    int bufSize = BUF_SIZE;
    int pos = 0;
    char* buffer = malloc(sizeof(char) * bufSize);
    
}

void shl_loop(void){
    char* line;
    char** args;
    int status;
    do{
        printf(">");
        line  = shl_read_line();
        args = shl_split_line(line);
        status = shl_execute(args);

        free(line);
        free(args);

    }while(status);

}

int main(){
    //Load config

    //Run command loop
    shl_loop();

    return 0;
}