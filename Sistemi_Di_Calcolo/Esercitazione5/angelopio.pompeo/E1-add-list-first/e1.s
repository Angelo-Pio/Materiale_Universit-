# Inserisci qui la soluzione...
.globl list_add_first

list_add_first:         # int list_add_first(node_t **l, short elem) {

    pushl %ebx
    pushl %esi
    
    subl $4,%esp
    xorl %eax,%eax

    movl 16(%esp),%esi # *p = *l
    movl (%esi),%ebx

    movl $8,(%esp) # sizeof node_t
    
    call malloc
    cmpl $0,%eax
    je E0

    movl 20(%esp),%edx
    movw %dx,(%eax) # n->elem = elem
    movl %ebx,4(%eax)

    movl %eax,(%esi)
    movl $0,%eax

    jmp E

E0:

    movl $1,%eax

E:
    addl $4,%esp
    popl %esi
    popl %ebx
    ret     
