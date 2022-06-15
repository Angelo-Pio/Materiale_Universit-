# scrivere la soluzione qui...

.globl find

find: 

    xorl %ecx,%ecx  # int i = 0;
    movl 4(%esp),%eax # a = v
L:
    cmpl %ecx,8(%esp) 
    jl E     # if(n<i){goto E;}

    movl (%eax,%ecx,4),%edx

    cmpl %edx,12(%esp) #    if(v[i] == x){
    je E1 #         goto E1;
    
    incl %ecx
    #     i++;
    jmp L #    goto L;

E1:
    movl $1,%eax
    jmp R
    
    #    return 1;
E:
    movl $0,%eax
    
    #    return 0;
R:
    ret
