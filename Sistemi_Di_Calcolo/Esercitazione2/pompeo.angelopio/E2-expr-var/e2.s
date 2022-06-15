# scrivere la soluzione qui...

.globl f

f:
    
    movl 4(%esp),%edx

    movl %edx,%eax
    imull %eax,%eax
    imull $2,%eax

    movl $7, %ecx
    imull %edx,%ecx

    subl %ecx,%eax
    incl %eax

    ret
    
