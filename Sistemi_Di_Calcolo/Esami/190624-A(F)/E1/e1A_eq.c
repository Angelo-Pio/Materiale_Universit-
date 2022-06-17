// inserire il C equivalente qui...
#include "e1A.h"
void init_matrix(short** m, unsigned n) {
    unsigned c = 0;
    unsigned d = 0;
    short** si = m;
L:
    if(c>=n) goto E;
    d = 0;

L1:
    if(d >= n) goto L2;

        int a = value(c,d);
        si[c][d] = a;

    d++;
    goto L1;
L2:
    c++;
    goto L;
E:
    return;    
}