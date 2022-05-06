// inserire il C equivalente qui...
#include "e1.h"



int is_prefix(const char* s1, const char* s2){

    const char* b = s1;
    const char* c = s2;
    int a = 1;
L:

    if(*b == '\0'){
        goto E;
    }

    if(*b != *c){
        goto E1;
    }


    b += 1;
    c += 1;

    goto L;

E1: 
    a = 0;

E:
    return a;

}