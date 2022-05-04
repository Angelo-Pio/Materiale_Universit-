//SCRIVERE LA SOLUZIONE QUI...

#include "e1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

