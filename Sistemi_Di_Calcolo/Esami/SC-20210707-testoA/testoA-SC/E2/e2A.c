#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "e2A.h"
// inserisci la soluzione qui...
int wordWithMaxCount(const char* text, const char c, char ** word){

    char * str = (char*) malloc((strlen(text)+1));
    strcpy(str,text);

    int max_count = 0;

    char* max_word = NULL; //questo

    char* token = strtok(str," ");
    while (token != NULL)
    {
        int size_token = strlen(token);
        int count  = 0;


        for (int i = 0; i < size_token; i++)
        {
            if(token[i] == c){
                count++;
            }
        }
        if(count > max_count){
            max_count = count;
            free(max_word);
            
            max_word = (char*) malloc((size_token)+1);
            strcpy(max_word,token);
        }        

        token = strtok(NULL," ");
    }
    
    free(str);
    *word = max_word;
    return max_count;
}

  