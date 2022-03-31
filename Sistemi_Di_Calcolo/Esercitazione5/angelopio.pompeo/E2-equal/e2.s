# Inserisci la soluzione qui...
.globl list_equal

list_equal: # int list_equal(const node_t *l1, const node_t *l2) {
    pushl %ebx
    pushl %esi
    movl 12(%esp), %ecx      # const node_t* c = l1;
    movl 16(%esp), %edx      # const node_t* d = l2;

L:
    testl %ecx,%ecx         # if(c == 0) goto E;
    je E
    
    testl %edx,%edx         # if(d == 0) goto E;
    je E
    
    movw (%ecx),%si         # si = c->elem
    movw (%edx),%bx         # bx = d->elem

    testw %si,%bx         # if(c->elem != d->elem) goto F
    jne F

        movl 4(%ecx),%ecx    # c = c->next;
        movl 4(%edx),%edx    # d = d->next;
    
    jmp L                   # goto L;

F:
    movl $0,%eax          # int a = 0;
    jmp S

E:
    testl %ecx,%ecx        # a = (c == d) ? 1 ; 0; 
    setz %al
    testl %edx,%edx        # a = (c == d) ? 1 ; 0; 
    setz %ah

    andb %ah,%al
    movsbl %al,%eax
S:
    popl %esi
    popl %ebx
    ret
