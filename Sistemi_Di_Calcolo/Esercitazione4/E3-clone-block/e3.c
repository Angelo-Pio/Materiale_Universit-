#include <stdlib.h>
#include <string.h>

void* clone(const void* src, int n) {
    void* des = malloc(n);
    if (des==0) return 0;
    memcpy(des, src, n);
    return des;
}

clone:

    int di;
    int si;
    int b;

    b = src;
    di = n;

    a = malloc(di);
    si = a; 

    memcpy(si,b,di)

    if(si == 0) goto E

    a = si

    return a
E:
    a = 0;
    return a;
