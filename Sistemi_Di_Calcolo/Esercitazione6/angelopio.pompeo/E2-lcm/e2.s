# Scrivere la soluzione qui...
.globl lcm

lcm : # int lcm(int x, int y) {

    pushl %ebx
    pushl %esi
    pushl %edi


    
    movl 16(%esp),%esi          # int c = x
    movl 20(%esp),%edi          # int a = y

    movl %edi,%ecx              # int b = a;

    cmpl %edi,%esi              # if(x > y) a = x;
    cmovg %esi,%ecx

L:

    movl %ecx, %eax         # a = c; // setta d in modo opportuno!
    movl %eax, %edx
    sarl $31, %edx
    idivl %esi              # int d = a % si;
    testl %edx, %edx        # char bl = d == 0;
    setzb %bl
    movl %ecx, %eax         # a = c; // setta d in modo opportuno!
    movl %eax, %edx
    sarl $31, %edx
    idiv %edi               # d = a % di;
    testl %edx, %edx        # char bh = d == 0;
    setzb %bh
    andb %bh, %bl
    jne E

    incl %ecx
    jmp L

E:    # Epilogo
    movl %ecx,%eax

    popl %edi
    popl %esi
    popl %ebx
    ret
