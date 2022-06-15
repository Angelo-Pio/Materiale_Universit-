#include "e1.h"

void bubble_sort(short *v, unsigned n)
{

    int c = n;
    int a = 0;  // do..
    int d = 1;
    goto L1;
L:

    if( a == 0) goto E; 
    
    a = 0;
    d = 1;

L1: //for
    // short* si = v;
    // short* di = v;

        if(d >= c) goto L; //i < n

        // d-=1;
        // *si = si[d];

        // d+=1;
        // *di = di[d];

        if(v[d-1] > v[d]){
             swap(&v[d-1],&v[d]);
             a = 1 ;
        }
    
    
    ++d;
    goto L1; //while

E:
    return;
}
