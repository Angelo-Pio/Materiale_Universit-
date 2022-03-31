// Scrivere il C equivalente qui...


int binsearch(int *v, int n, int x) {

    int c = 0;
    int b = n;
    int* si = v;
    int a = 0;
    int d = 0;
L:    
    if(c == b) goto E ;

        d = (c+b)>>1;

        if(si[d]==x) goto F;

        if(si[d] > x) {
            b = d;
        }
        else{
            c = d+1;
        }


    goto L;

F: 
    a = 1;
E:
    return a;    


}