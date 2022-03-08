# scrivere la soluzione qui...
.globl f

f:

    movl 4(%esp),%eax
    movl 8(%esp),%ecx
    
    
    movl 4(%esp),%edx 

    subl %ecx,%edx

    addl %ecx,%eax

    imull %edx,%eax

    ret
    


    
