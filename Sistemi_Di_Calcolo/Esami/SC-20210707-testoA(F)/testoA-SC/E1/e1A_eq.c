// inserire il C equivalente qui...
#include "e1A.h"
int suffix(const char* a, const char* b) {

    const char* si = a;
    const char* di = b;
    int res = 1;

    int c = strlen(si);
    int d = strlen(di);

    int bi = c - d ;

    if(d > c) goto E0;
L:        

    if(bi >= c) goto E1;

    if(si[bi] != *di++) goto E0;

    bi++;
    goto L;

E0:
    res = 0;    
    
E1:    
    return res;
}