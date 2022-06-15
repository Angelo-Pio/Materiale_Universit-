// scrivere la soluzione qui...

.globl my_strcmp

my_strcmp:

   xorl %edx,%edx

L:
   movl 4(%esp),%eax     
   movl 8(%esp),%ecx 
    
    movb (%eax,%edx,1),%al
    movb (%ecx,%edx,1),%cl

    cmpb $0,%al
    je E


    cmpb %al,%cl
    jne E  



    incl %edx
    jmp L

E:
    subl %ecx,%eax
    ret
    


    
    