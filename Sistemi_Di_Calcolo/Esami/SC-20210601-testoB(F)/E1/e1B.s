# inserire la soluzione qui...
.globl adler32_simplified


 adler32_simplified: # unsigned int adler32_simplified(unsigned char* data, int len) {
    
    # Prologo
    pushl %esi
    pushl %ebx

    movl $0,%ecx # int c = 0; 
    movl $0,%edx # unsigned int d = 0, a = 1;
    movl $1,%eax
    movl 12(%esp),%esi # unsigned char* si = data;

L:
    cmpl 16(%esp),%ecx #  if(c >= len) goto E;
    jge E
    
        movb (%esi,%ecx,1),%bl # int b = si[c];

        movzbl %bl,%ebx


        addl %ebx,%eax # a = a + b;
        andl $0xFFFF,%eax # a = a & 0xFFFF;


        addl %eax,%edx # d = d + a;
        andl $0xFFFF,%edx #d = d & 0xFFFF; 

    incl %ecx # c++;
    jmp L # goto L;
E:
    shll $4,%edx  # d = d << 16;
    orl %edx,%eax # a = d|  a;

    popl %ebx
    popl %esi
    ret # return  a;


# 
# len 16
# data 12
# rit 8
# si 4
# b 0
# 

