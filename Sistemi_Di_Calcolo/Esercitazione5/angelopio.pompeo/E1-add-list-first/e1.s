# Inserisci qui la soluzione...
.globl list_add_first

list_add_first:         # int list_add_first(node_t **l, short elem) {

    pushl %ebx
    pushl %edi
    subl $4,%esp
    
    movl 16(%esp),%edi  #si = *l
    movl (%edi), %ebx

    
    movl $8,(%esp)      # c = sizeof(si)
    call malloc         # a = malloc(c)

    cmpl $0,%eax        #if(a==NULL) goto E
    jnz E

    movl $1,%eax
    jmp F

E:
    movl 20(%esp),%edx
    movw %dx,(%eax)
    movl %ebx,4(%eax)

    movl %eax,(%edi)
    xorl %eax,%eax
F:           
    addl $4,%esp
    popl %edi
    popl %ebx
    ret
    
