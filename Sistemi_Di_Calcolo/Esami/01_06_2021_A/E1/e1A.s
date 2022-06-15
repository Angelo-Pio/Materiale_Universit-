# inserire la soluzione qui...
.globl count_tokens

count_tokens: # int count_tokens(char* str, const char* sep) {
    
    pushl %ebx
    pushl %esi
    pushl %edi
    subl $8,%esp
    xorl %ecx,%ecx # int c = 0;
    
    movl 24(%esp),%ebx # char* b = str;
    movl 28(%esp),%esi # const char* si = sep;


    #     char * c = strtok(b,si);
    movl %ebx,(%esp)
    movl %esi,4(%esp)
    call strtok
    movl %eax,%esi

L:
    cmpl $0,%esi #  if(c == NULL) goto E;
    je E
        

        movl $0,%ebx # b = 0;
        movl %ebx,(%esp)

        call strtok # a = strtok(b,si);

        movl %eax,%esi
        incl %ecx #c++;
    
    jmp L # goto L;

E:
    movl %ecx,%eax

    addl $8,%esp
    popl %esi
    popl %ebx

	ret # return a;


# y 24
# x 20 
# rit 16
# bi 12
# si 8
# par2 -> 4
# par1
