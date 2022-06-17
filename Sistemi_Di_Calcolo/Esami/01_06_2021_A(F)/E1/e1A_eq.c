// inserire il C equivalente qui...
#include "e1A.h"

int count_tokens(char* str, const char* sep) {

    int b = 0;

    const char* esi = sep;
    char* c = str;

    char* a = strtok(c,esi);

L:
    if(a  == 0) goto E;
        a = strtok(NULL,esi);
    b++;
    goto L;

E:
    
    return b;    

}