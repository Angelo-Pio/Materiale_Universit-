// inserire il C equivalente qui...
#include "e1B.h"
int has_duplicates(short* v, unsigned n) {

    short* si = v;
    unsigned c = 0;
    unsigned d = c+1;
    int a = 0;

L:
    if(c >= n) goto E;
    d = c+1;

L1:        

    if(d >= n ) goto L2;

        if (si[c] == si[d]) goto E0;

    d+=1;
    goto L1;
L2:
    c++;
    goto L;
E0:
    a = 1;

E:       
    return a;
}