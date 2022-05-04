//SCRIVI LA SOLUZIONE QUI...

#include "e2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void get_cmd_line(char* argv[MAX_TOKENS]){

    int i = 0; 
    char* line_scanned = (char*)malloc(1024 * sizeof(char));
    fgets(line_scanned,MAX_LINE,stdin);
    char* token = strtok(line_scanned ," \t\n");

    while(i < MAX_TOKENS && token != NULL)
    {

        char* line = malloc(strlen(token)+1);
        strcpy(line,token);

        argv[i]  = line;
        token = strtok(NULL," \t\n");
        i++;
    }

    argv[i] = NULL;
}

int do_cmd(const char* command[]){

    pid_t pid = fork();

    if(pid == -1){
        perror("fork error") ;
        exit(EXIT_FAILURE);
    }
    if(pid == 0){

        execvp(command[0],command);
        printf("execvp Unknown Command %s\n",command[0]);
        _exit(EXIT_FAILURE);
    }

    pid = wait(NULL);

    if(pid == -1){
        perror("Wait");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;

}

void deallocate_cmd(char* argv[MAX_TOKENS]) {
	while (*argv != NULL)
		free(*argv++);
}

int do_shell(const char* prompt){

    while (1)
    {
        printf("%s",prompt);
        char* command[MAX_TOKENS];
        get_cmd_line(command);


        if(strcmp(command[0],"quit") == 0){
            break;
        }
        if(command[0] == NULL){
            continue;
        
            do_cmd(command);
            deallocate_cmd(command);
        
    }

    return EXIT_SUCCESS;
}

