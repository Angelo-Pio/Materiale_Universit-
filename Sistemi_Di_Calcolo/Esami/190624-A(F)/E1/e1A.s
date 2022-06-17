# inserire la soluzione qui...
.globl init_matrix

init_matrix: #void init_matrix(short** m, unsigned n) {
    
    pushl %esi # c 
    pushl %edi  # d
    pushl %ebx # m
    pushl %ebp
    subl $8,%esp

    xorl %edi,%edi # unsigned c = 0;
    xorl %esi,%esi # unsigned d = 0;
    
    movl 28(%esp),%ebp # short** si = m;
L:
    cmpl 32(%esp),%esi # if(c>=n) goto E;
    jge E

    movl $0,%edi # d = 0;

L1:
    cmpl 32(%esp),%edi # if(d >= n) goto L2;
    jge L2

        movl %esi,(%esp)
        movl %edi,4(%esp)
        call value

        movl (%ebp,%esi,4),%ecx
        movw %ax,(%ecx,%edi,2)


    incl %edi # d++;
    jmp L1 # goto L1;
L2:
    incl %esi # c++;
    jmp L # goto L;
E:
    addl $8,%esp
    popl %ebp
    popl %ebx # m
    popl %edi  # d
    popl %esi # c 
    ret

# n 32
# m 28
# rit 24
# si 20
# di 16
# b 12
#bp 8
# y 4
# x 0









    