.globl counteq

counteq:

    pushl %esi
    pushl %edi

    xorl %eax,%eax # a = 0 counter
    xorl %edx,%edx # d = 0 i

L:
    movl 12(%esp),%esi
    movl 16(%esp),%edi
    
    cmpl 20(%esp),%edx
    jge E 

        movw (%esi,%edx,2),%si
        movw (%edi,%edx,2),%di

        cmpw %si,%di
        sete %cl

        movzbl %cl,%ecx
        addl %ecx,%eax

    incl %edx
    jmp L

E:
    popl %edi
    popl %esi

    ret
    

