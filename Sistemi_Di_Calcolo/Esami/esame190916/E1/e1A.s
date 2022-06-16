# inserire la soluzione qui...
.globl is_prefix

is_prefix:      # int is_prefix(const char* s, const char* t) {

    pushl %ebx
    pushl %edi
    pushl %esi


    movl $0,%edx    # int d = 0;

L:  

    movl 16(%esp),%esi  # const char* si = s;
    movl 20(%esp),%edi  #  const char* di = t;
    

    movb (%esi,%edx,1),%al  # char a = si[d];    
    movb (%edi,%edx,1),%bl  # char b = di[d];    

    movb %al,%cl # char c = a && b;
    andb %bl,%cl 

    cmpb $0,%cl # if(!c) goto E;
    je E

    cmpb %al,%bl  #  if(a != b) goto E;
    jne E 
    
    andb %bl,%al
    notb %al
    andb %cl,%al
    
    incl %edx       # d++;
    jmp L           # goto L;

E:

    cmpb $0,%al
    sete %cl

    movzbl %cl,%eax
    popl %esi
    popl %edi
    popl %ebx
    ret

# 22" 
# t 20
# s 16
# rit 12 
# b 8
# di 4
# si 0






