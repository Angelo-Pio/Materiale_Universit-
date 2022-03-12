.glob fact

fact:

    movl $1, %eax
    movl $3, %ecx
    movl 4(%esp), %edx

L: 
<<<<<<< HEAD
    compl %edx,%ecx # c - d 
    ja E            # c > 0
    imull %ecx,%eax # a = c*a
    incl %ecx       # c++
    jmp L           # loop
=======
    compl %edx,%ecx
    ja E
    imull %ecx,%eax
    incl %ecx
    jmp L
>>>>>>> bad246bf7f37b1b5bbfe64fb02b97f9a802177fe

E: 
    ret
