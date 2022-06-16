# inserire la soluzione qui...
.globl suffix

suffix: # int suffix(const char* a, const char* b) {

    pushl %esi
    pushl %edi
    pushl %ebx
    pushl %ebp
    subl $4,%esp

    movl 24(%esp), %esi # const char* si = a;
    movl 28(%esp),%edi # const char* di = b;

    movl %esi,(%esp) # int c = strlen(si);
    call strlen
    movl %eax,%ebp

    movl %edi,(%esp) #int d = strlen(di);
    call strlen
    movl %eax,%edx

    cmpl %ebp,%edx # if(d > c) goto E0;
    jg E0

    movl %ebp,%ebx # int bi = c - d ;
    subl %edx,%ebx


L:        

    cmpl %ebp,%ebx #  if(bi >= c) goto E1;
    jge E1

    movb (%edi),%al


    cmpb (%esi,%ebx), %al   #     if(si[bi] != *di++) goto E0;
    jne E0


    incl %edi # di++;
    incl %ebx # bi++;
    jmp L # goto L;

E0:
    movl $0,%eax # res = 0;    
    jmp E2 
E1:
    movl $1,%eax
E2:
    addl $4,%esp
    popl %ebp
    popl %ebx
    popl %edi
    popl %esi
    ret
# 
# b 28
# a 24
# rit 20
# si 16
# di 12
# bi 8
# y 4
# x 0
# 



