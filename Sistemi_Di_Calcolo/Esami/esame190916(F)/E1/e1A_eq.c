// inserire il C equivalente qui...
int is_prefix(const char* s, const char* t) {

    const char* si = s;
    const char* di = t;

    int d = 0;

L:  

    char a = si[d];    
    char b = di[d];    

    char c = a && b;

    if(!c) goto E;
    
    if(a != b) goto E;

    d++;
    goto L;

E:
    a = a == 0;
    return a;     

}