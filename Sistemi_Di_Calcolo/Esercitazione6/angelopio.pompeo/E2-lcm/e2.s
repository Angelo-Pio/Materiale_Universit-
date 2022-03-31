# Scrivere la soluzione qui...
.globl lcm

lcm : # int lcm(int x, int y) {

    pushl %ebx
    pushl %esi
    pushl %edi


    movl 20(%esp),%eax          # int a = y;
    movl 16(%esp),%ecx          # int c = x


    cmpl %ecx,%eax              # if(x > y)goto E0;
    jg E0

L:  
    int b = a % x ;
    int si = a % y ;

        b = b == 0;
        si = si == 0;

        int di = b & si;

        if(di) goto E;

        incl %eax               # a += 1;    

    jmp L                       # goto L;

E0:
    movl 16(%esp),%eax          # a = x;
    jmp L                       # goto L;
E:
    popl %ebx
    popl %esi
    popl %edi
    ret                         # return a;    


}