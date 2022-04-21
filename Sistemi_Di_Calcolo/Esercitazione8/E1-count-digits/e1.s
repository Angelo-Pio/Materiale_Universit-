.globl count_digits

count_digits:               # int count_digits(const char *s) 
    pushl %ebx
	xorl %eax , %eax        # int a = 0;
	xorl %edx , %edx        # int d = 0;
    movl 8(%esp),%ecx       # const char* c = s;
L:
    movb (%ecx,%edx,1),%bl
    cmpb $0,%bl            # if(*c == 0){goto E;}
    je E
		
        cmpb $48,%bl    # if (*c < 48 && *c > 57) a++;
        jl D
        cmpb $57,%bl
        jg D

        incl %eax
		jmp D         # c = c+1;

    jmp L                               # goto L;
D:
   incl %edx
   jmp L
E:	
    popl %ebx
	ret                     # return a;
