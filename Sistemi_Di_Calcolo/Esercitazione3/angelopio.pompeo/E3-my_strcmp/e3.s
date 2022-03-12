// scrivere la soluzione qui...

.globl my_strcmp

my_strcmp:

    movl	$0, %ecx


M:

    movl    8(%esp),%edx
    movb    (%edx,%ecx,1),%dl

    movl    4(%esp),%eax
    movb    (%eax,%ecx,1),%al

    cmpb %dl,%al
    jne E

    incl %ecx
    jmp M



E:
    subb %dl,%al
    ret

    
    
    