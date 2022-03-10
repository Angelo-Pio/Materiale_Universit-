.glob fact

fact:

    movl $1, %eax
    movl $3, %ecx
    movl 4(%esp), %edx

L: 
    compl %edx,%ecx
    ja E
    imull %ecx,%eax
    incl %ecx
    jmp L

E: 
    ret
