# scrivere la soluzione qui...

.globl fib

fib:

    pushl %esi
    pushl %ebx
    subl $4,%esp

    movl 16(%esp),%esi #si = n
    movl $1,%eax        #a = 1

    cmpl $2,%esi # si < 2
    jl E            # goto E

    decl %esi     #si--
    movl %esi,(%esp) #passaggio val

    call fib # fib(si-1)

    movl %eax,%ebx # b = a 

    decl %esi     #si--
    movl %esi,(%esp)
    call fib

    addl %ebx,%eax



E:
    addl $4,%esp
    popl %ebx
    popl %esi
    ret








    #c = n
    #if(c < 2) goto E
    #b = fib(c-1)
    # a = fib(c-2)
    #   return a + b
    #
    # E
    #    a = 1
    #    return a 