# scrivere la soluzione qui...

.globl fib

fib:

    movl 4(%esp),%ecx
    pushl %esi

    L:

        cmpl $2,%ecx
        jl E 

        pushl %ebx
        call fib
                


        jmp L


    E:
        movl $1,%eax

        popl %ebx
        popl %esi
        ret








    #c = n
    #if(c < 2) goto E
    #
    #return fib(c-1) + fib (c-2)
    #
    #
    # E
    #    a = 1
    #    return a 