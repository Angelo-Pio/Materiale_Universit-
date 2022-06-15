# Inserisci la soluzione qui...
.globl list_equal

list_equal: # int list_equal(const node_t *l1, const node_t *l2) {

    pushl %ebx
    pushl %esi
    pushl %edi


    movl 16(%esp),%esi #     const node_t* si = l1;
    movl 20(%esp),%edi #   const node_t* di = l2;
    xorl %eax,%eax # int a = 0


L:  
    #   if(si == 0){
    #       goto E1;
    #   }
    #       if(di == 0){
    #           goto E1;
    #       }

    cmpl $0,%esi
    je E1
    cmpl $0,%edi
    je E1

    movw (%esi),%cx #    short c = l1->elem;
    movw (%edi),%dx #    short d = l2->elem;

    cmpw %cx,%dx # if(c != d){
    jne E   #    goto E;
    

    movl 4(%esi),%esi # si = si->next;
    movl 4(%edi),%edi # di = di->next;
    jmp L              # goto L;


E1:

    cmpl $0,%esi
    sete %al

    cmpl $0,%edi
    sete %bl

    andb %bl,%al    

    movzbl %al,%eax

    # if(si == 0){
    #     a = si == di ? 1 ; 0
    # 

E:
    popl %edi
    popl %esi
    popl %ebx
    ret

#l2 20
#l1 16
#rit 12
#b 8
#si 4
#di 0
