// inserire il C equivalente qui...
unsigned int adler32_simplified(unsigned char* data, int len) {
    
    int c = 0; 
    unsigned int d = 0, a = 1;
    unsigned char* si = data;

L:

    if(c >= len) goto E;

    int b = si[c];

    a = a + b;
    a = a & 0xFFFF;

    d = d + a;
    d = d &0xFFFF; 

    c++;
    goto L;

E:
    d = d << 16;
    a = d |  a;
    return  a;
}