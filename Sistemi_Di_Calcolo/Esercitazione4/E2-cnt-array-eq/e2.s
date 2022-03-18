
.globl counteq

counteq:

    pushl %ebx
    pushl %esi
    pushl %edi

    movl 16(%esp),%edi
    movl 20(%esp),%esi
    movl 24(%esp),%edx
    xorl %eax,%eax # a = 0
    decl %edx

L:    testl %edx,%edx
    jl E                # goto E

        movw (%edi,%edx,2), %cx # c = vi1[i]
        movw (%esi,%edx,2), %bx # b = vi2[i]

        cmpw %cx,%bx
        sete %cl
        movsbl %cl,%ecx
        addl %ecx,%eax


    decl %edx
    jmp L
E:
    popl %edi
    popl %esi
    popl %ebx

    ret


# int c = 0;
# int a = 0;
# 
# 

# 
#   short b = *(vi1 + c)
#   short d = *(vi2 + c)
#     if(*(b+c) == *(d+c)) a++
# 
# return a 
