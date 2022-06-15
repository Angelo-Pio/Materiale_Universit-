#include <stdio.h>

int find(int* v, int n, int x) {
    int i = 0;
    
L:
        if(i > n){goto E;}

        if(v[i] == x){
            goto E1;
        }
        i++;
        goto L;

E1:
        return 1;
E:
        return 0;

}

