# scrivere la soluzione qui...

.globl is_prefix

is_prefix: # int is_prefix(const char* s1, const char* s2)

    pushl %ebx
    pushl %edi
    pushl %esi

    movl 16(%esp),%esi  # si = s1
    movl 20(%esp),%edi  #di = s2

    xorl %ecx,%ecx              # c = 0;
    movl $1,%eax                # int a = 1;


L:
    movb (%esi,%ecx,1),%dl    # d = *s1
    movb (%edi,%ecx,1),%bl   # b = *s2

        cmpb $0,%dl
        je E 
        
        cmpb %bl,%dl
        jne E1 

        
    incl %ecx
    jmp L                   #  goto L;

E1: 
    xorl %eax,%eax          #     a = 0;

E:

    popl %esi
    popl %edi
    popl %ebx

    ret             # return a;
