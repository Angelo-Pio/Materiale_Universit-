# Scrivere la soluzione qui...

.globl list_concat

list_concat:    #   void list_concat(node_t **l1, node_t *l2) {




    movl 4(%esp), %eax      #  node_t *a = l1;
    movl 8(%esp), %ecx          
    movl (%eax),%edx        # d = *l1


    cmpl $0,%edx            # if(a == NULL) go;
    je L 

R:  
    movl 4(%eax),%edx
    cmpl $0,%edx            # if(a->next == NULL) goto E;
    je E 
    
    movl 4(%eax),%eax       # a = a->next;    

    jmp R                   # goto R;

L: 
    movl %ecx,(%eax)         # *l1 = l2;
    ret                     # return ;

E:
    movl %ecx,4(%eax)      # a->next = l2;
    ret                     # return ;

