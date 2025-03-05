#include <stdio.h>
#define BUF_SIZE 1024

char* shl_reaf_line(void){
    char* line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us

    if (getline(&line, &bufsize, stdin) == -1){
        if (feof(stdin)) {
        exit(EXIT_SUCCESS);  // We recieved an EOF
        } else  {
        perror("readline");
        exit(EXIT_FAILURE);
        }
    }

  return line;
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