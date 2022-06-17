# inserire la soluzione qui...
.globl count_tokens

count_tokens: # int count_tokens(char* str, const char* sep) {

    pushl %edi
    pushl %esi
    pushl %ebx
    subl $8,%esp


    movl $0,%ebx # int b = 0;

    movl 28(%esp),%esi # const char* esi = sep;
    movl 24(%esp),%edi # char* c = str;

    movl %edi,(%esp)
    movl %esi,4(%esp)
    call strtok
    # char* a = strtok(c,esi);

L:
    cmpl $0,%eax # if(a  == 0) goto E;
    je E 

        movl $0,(%esp)
        movl %esi,4(%esp)
        call strtok # a = strtok(NULL,esi);

    incl %ebx # b++;
    jmp L # goto L;

E:
    movl %ebx,%eax

    addl $8,%esp
    popl %ebx
    popl %esi
    popl %edi
    ret # return b;    
#sep 28
#str 24
#rit 20
#di 16
#si 12
#b 8
#y 4
#x 0
