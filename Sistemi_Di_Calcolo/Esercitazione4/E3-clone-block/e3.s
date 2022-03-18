# scrivere la soluzione qui...

.globl clone

clone:  #   void* clone(const void* src, int n) 

    pushl %edi                          #    int di;
    pushl %esi                          #    int si;
    pushl %ebx                          #    int b;
    subl $12, %esp                      #    
                                        
    movl 28(%esp), %ebx                 #    b = src;
    movl 32(%esp), %edi                 #    di = n;

    movl %edi,(%esp)                  #
    call malloc                         #    a = malloc(di);
    movl %eax,%esi                      #    si = a; 

    xorl %eax,%eax

    cmpl $0,%esi                        #    if(si == 0)
    je E                                #    goto E

    # Passaggio parametri a funzione
    movl %esi,(%esp)
    movl %ebx,4(%esp)
    movl %edi,8(%esp)

    
    
    call memcpy                         #    memcpy(si,b,di)
    #

    movl %esi,%eax                      #    a = si

    
E: 
    addl $12,%esp
    popl %ebx
    popl %esi
    popl %edi
    ret                                 #  return a;
