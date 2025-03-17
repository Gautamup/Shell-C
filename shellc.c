#include <stdio.h>
#define BUF_SIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

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

char **shl_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
  
    if (!tokens) {
      fprintf(stderr, "lsh: allocation error\n");
      exit(EXIT_FAILURE);
    }
    
    token = strtok(line, LSH_TOK_DELIM);
    
    while (token != NULL) {
        tokens[position] = token;
        position++;
    
        if (position >= bufsize) {
          bufsize += LSH_TOK_BUFSIZE;
          tokens = realloc(tokens, bufsize * sizeof(char*));
          if (!tokens) {
            fprintf(stderr, "lsh: allocation error\n");
            exit(EXIT_FAILURE);
          }
        }
    
        token = strtok(NULL, LSH_TOK_DELIM);
      }
      tokens[position] = NULL;
      return tokens;
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