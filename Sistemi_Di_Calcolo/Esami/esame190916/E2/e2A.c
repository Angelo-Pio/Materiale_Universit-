#include "e2A.h"
#include <stdlib.h>
#include <string.h>

void multi_get_env(const char** names, char*** values, int num) {
    
    char** res = (char**) malloc(num*sizeof(char*));

    for (int i = 0; i < num; i++)
    {
        char* env = getenv(names[i]);
        if(env == NULL){
            res[i] = NULL;
        }else{

        int size = strlen(env) + 1;

        res[i] = (char*)malloc(size*sizeof(char));
        strcpy(res[i],env);

        }
        
    }

    *values = res;
    

} 
