# inserire la soluzione qui...
.globl bubble_sort

bubble_sort:    # void bubble_sort(short *v, unsigned n)

    # unsigned i, again;
    
    pushl %ebx  #v[i-1]
    pushl %edi  #v[i]
    subl $8,%esp


    xorl %ecx,%ecx # c = i
    movl 24(%esp),%edx    # d = n

L:
    xorl %eax,%eax      #    again = 0;
    movl $1,%ecx        # i = 1;

E:
    cmpl %edx,%ecx      #if (i >= n)
    jge L1              # goto L1;
    
        movl 20(%esp),%ebx

        movw (%ebx,%ecx,2),%di

        decl %ecx
        movw (%ebx,%ecx,2),%bx
        incl %ecx

            cmpw %di,%bx # if (v[i - 1] > v[i])
            jng E0

            movl %ebx,(%esp)    
            movl %edi,4(%esp)    
            # swap(&v[i - 1], &v[i]);
            call swap
            movl $1,%eax # again = 1;


E0:
    incl %ecx           # ++i;
    jmp E               # goto E;
L1:

    cmpl $1,%eax  # if (again)
    je L          # goto L;
    
R:
    addl $8,%esp
    popl %edi
    popl %ebx
    ret

# void bubble_sort(short *v, unsigned n)
# {
#     unsigned i, again;
# 
# L:
#     again = 0;
#     i = 1;
# 
# E:
#     if (i >= n)
#     {
#         goto L1;
#     }
#         if (v[i - 1] > v[i])
#         {
#             swap(&v[i - 1], &v[i]);
#             again = 1;
#         }
# 
#     ++i;
#     goto E;
# L1:
# 
#     if (again)
#     {
#         goto L;
#     }
# 
#     return;
# }