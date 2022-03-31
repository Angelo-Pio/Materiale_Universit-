// Scrivere il C equivalente qui...

#include "e2.h"

int lcm(int x, int y) {

    int a = y;

    if(x > y)goto E0;

L:  
    int b = a % x ;
    int si = a % y ;

        b = b == 0;
        si = si == 0;

        int di = b & si;

        if(di) goto E;

        a += 1;    

    goto L;

E0:
    a = x;
    goto L;
E:
    return a;    


}