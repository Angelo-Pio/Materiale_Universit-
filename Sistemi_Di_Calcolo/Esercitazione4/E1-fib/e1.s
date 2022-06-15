# scrivere la soluzione qui...

.globl fib

fib:        # int fib(int n) 

    pushl %ebx
    pushl %esi

    subl $4,%esp


    movl 16(%esp),%ebx #  int b = n;
    movl $1,%eax # int a = 0;

    cmpl $2,%ebx # if(b < 2){
    jl E #     goto E;
    
    decl %ebx
    movl %ebx,(%esp) #c = fib(b-1)
    call fib
    
    movl %eax,%esi


    decl %ebx
    movl %ebx,(%esp) #c = fib(b-1)
    call fib

    addl %esi,%eax

     # a = c + d 
    # return a ;


    E: 
        addl $4,%esp
        popl %esi
        popl %ebx
        ret








