#include <stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

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

char shl_launch(char **args){
  pid_t,wpid;
  int status;
  pid = fork();
  //child process pid == 0
  if(pid == 0){
    if(execvp(args[0],args) == -1){
      perror('shl');
      exit(EXIT_FAILURE);
    }
  } else if(pid <0){
    perror('shl');
  } else{
    do{
      wpid = waitpid(pid,&status,WUNTRACED);
      }while(!WIFEXITED(status) && !WIFSIGNALED(status))
  }
}

int shl_cd(char **args);
int shl_help(char **args);
int shl_exit(char **args);
char *bultin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &shl_cd,
  &shl_help,
  &shl_exit
};

int shl_num_builtins(){
  return sizeof(bultin_str)/sizeof(char *);
}

int shl_cd(char **args){
  if(args[1] == NULL){
    fprintf(stderr,"shl: expected argument to \"cd\"\n");
  }
  else{
    if(chdir(args[1]) != 0){
      perror("shl");
    }
  }
  return 1;
}

int shl_help(char **args){
  printf("!!!! Welcome to SHL !!!!\n");
  printf("Type program name and agruements, then hit enter.\n");
  printf("Type of builtin are:\n");

  for(int i=0;i<shl_num_builtins();i++){
    printf(" %s\n", bultin_str[i]);
  }
  printf("Use the man command for information on other programs.\n");
  return 1;
}

int shl_exit(char **args){
  return 0;
}

int shl_execute(char **args){
  if(args[0] == NULL){
    //Entered empty command
    return 1;
  }
  for(int i=0;i<shl_num_builtins();i++){
    if(strcmp(args[0],bultin_str[i]) == 0){
      return (*builtin_func[i])(args);
    }
  }
  return shl_launch(args);
}

void shl_loop(void){
    char* line;
    char** args;
    int status;
    bool check = true;
    do{
        printf(">");
        line  = shl_read_line();
        args = shl_split_line(line);
        int i = 0;
        while (args[i] != NULL) {
            if(args[i].isspace()){
              check = false;
              break;
            }
        }
        if(check){
          status = shl_execute(args);
        }
        free(line);
        free(args);

    }while(status);

}

int main(){
    //Load config

    //Run command loop
    shl_loop();

    return EXIT_SUCCESS;
}