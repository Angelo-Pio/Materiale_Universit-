// Scrivere il C equivalente qui...
//char charsi(const char* s) {
//    unsigned si[256];
//    memset(si, 0, 256*sizeof(unsigned));
//
//    while (*s) si[*s++]++;
//
//    unsigned maxi = 0;
//    unsigned maxf = si[0];
//    int i;
//    for (i=1; i<256; ++i){
//        if (si[i]>maxf) {
//            maxi = i;
//            maxf = si[i];
//        }
//    }
//    return maxi;
//}
#include <string.h>
#include "e3.h"

char charfreq(const char* s) {

    unsigned si[256];
    int c = 256 * sizeof(unsigned) ; // sizeof(si)
    memset(si,0,c);

    c = 0;

T:;  
    char di = s[c];
    if(di == 0) goto  TE;
        si[di]++;
        c++; 


    goto T;

TE:;
    unsigned a = 0;  // maxi
    unsigned d = si[0]; //maxf
    c = 1;      // i
L:
    
    if(c >= 256) goto E;

        
        if(si[c] > d) a = c;
        if(si[c] > d) d = si[c];

    ++c;
    goto L;

E:
    return a;



}