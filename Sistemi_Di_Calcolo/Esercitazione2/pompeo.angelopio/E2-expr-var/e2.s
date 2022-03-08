# scrivere la soluzione qui...

.globl f

f:
    
    movl 4(%esp),%eax

    imull %eax,%eax
    imull $2,%eax

    movl $7,%ecx
    imull 4(%esp),%ecx

    sub %ecx,%eax
    incl %eax

    ret

