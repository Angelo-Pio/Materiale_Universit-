// inserire il C equivalente qui...
#include "e1A.h"
int most_freq_char(const char* s, int* map) {

    int c = 0 , a = 0;

    int* si = map;
    const char* di = s;

    clear(si, 256);

L:  
    if(*di == 0) goto L1;
    
    int d = *di;
    d = si[d]+=1;
    // d++;

    di++;
    goto L;

L1:
    c = 0;

L2:
    if(c>= 256) goto E;
    
        if (si[c] > si[a]) a = c;


    c++;
    goto L2;

E:    
    return a;
}