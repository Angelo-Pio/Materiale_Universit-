# scrivere la soluzione qui...

.globl clone

clone:

    call malloc

    cmpl $0,8(%esp) # if(des == 0 ret 0)
    je E

    movl 4(%esp),%ecx
    movl 8(%esp),%edx

    subl	$12, (%esp)

    

    movl   %eax,4(%esp)
    movl   %ecx,8(%esp)
    movl   %edx,12(%esp)

    call memcpy



    ret
    


    E:
        movl $0,%eax
        ret
        
