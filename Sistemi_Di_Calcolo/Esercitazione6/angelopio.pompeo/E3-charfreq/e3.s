# Scrivere la soluzione qui...
.globl charfreq
charfreq: # char charfreq(const char* s) {

    pushl %esi
    pushl %edi
    pushl %ebx
    subl $1036,%esp # 256*4 + 12

    # movl unsigned si[256];

    leal 12(%esp),%esi

    movl %esi,(%esp)
    movl $0,4(%esp)
    movl $1024,8(%esp)
    call memset                                 # memset(si,0,c);

    xorl %ecx,%ecx                              # c = 0;

    movl 1052(%esp),%edi
T:;  
    movb (%esi),%dl                      # char di = s[c];
    movsbl %dl,%edi

    cmpl $0,%edi # if(di == 0) goto  TE;
    je TE
        
        incl (%esi,%edi,4)                      # si[di]++;


    incl %ecx # c++; 
    jmp T                           # goto T;

TE:;
    xorl %eax,%eax                  # unsigned a = 0;  // maxi
    movl (%esi),%edx                # unsigned d = si[0]; //maxf
    movl $1,%ecx                    # c = 1;      // i
L:
    
    cmpl $256,%ecx # if(c >= 256) goto E;
    jge E 

        movl (%esi,%ecx,4),%ebx

        testl %edx,%ebx             # if(si[c] > d) a = c;
        cmovgl %ecx,%eax

        testl %edx,%ebx             # if(si[c] > d) d = si[c];
        cmovgl %ebx,%edx

    incl %ecx                   # ++c;
    jmp L                       # goto L;

E:
    addl $1036,%esp
    popl %ebx
    popl %edi
    popl %esi

    ret                         # return a;