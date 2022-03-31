# Scrivere la soluzione qui...
.globl binsearch

binsearch: #int binsearch(int *v, int n, int x) {

    pushl %ebx
    pushl %esi
    

    xorl %eax,%eax      # int a = 0;
    xorl %ecx,%ecx      # int c = 0;
    
    movl 16(%esp),%ebx   # int b = n;
L:    
    testl %ecx,%ebx     # if(c == b) goto E ;
    jge E

        leal (%ebx,%ecx),%edx # int d = (c+b)/2;
        sarl %edx
        
        movl 12(%esp),%esi   # int* si = v;
        movl (%esi,%edx,4),%esi
        
        testl %esi,20(%esp)        # if(si[d]==x) goto F;
        je F

        cmpl 20(%esp),%esi         # if(si[d] > x) {
        cmovg %edx,%ebx            # b = d;
        
        leal 1(%edx),%ecx


    jmp L # goto L;

F: 
    movl $1,%eax        # a = 1;
E: 
    popl %esi
    popl %ebx
    ret

