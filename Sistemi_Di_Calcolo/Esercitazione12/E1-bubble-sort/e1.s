# inserire la soluzione qui...
.globl bubble_sort

bubble_sort:    # void bubble_sort(short *v, unsigned n)

    pushl %esi
    pushl %edi
    pushl %ebx
    subl $8,%esp


    movl $24,%ecx # int c = n;
    xorl %eax,%eax # int a = 0;  // do..
    movl $1,%ebx # int d = 1;
    jmp L1 # goto L1;
L:

    cmpl $0,%eax #if( a == 0) goto E; 
    je E

    movl $0,%eax     # a = 0;
    movl $1,%ebx     # d = 1;
    

L1: 
    # short* si = v;
    #  short* di = v;

        cmpl %ecx,%edx # if(d >= c) goto L; //i < n
        jge L 
        
    movl 20(%esp),%esi
    movl 20(%esp),%edi

    decl %edx 
    movw (%esi,%ebx,2),%si  #si = v[i-1]

    incl %edx
    movw (%edi,%ebx,2),%di #di = v[i]
      
    cmpw %si,%di #    if(v[d-1] < v[d]){
    jl L2       #goto L2

    leal -2(%esi,%ebx,2),%eax
    movl %eax,(%esp)
    
    
    leal (%esi,%ebx,2),%eax
    movl %eax,4(%esp)

    call swap      # swap(&v[d-1],&v[d]);
    movl $1,%eax   # a = 1 ;
             

L2:    
    incl %ebx # ++d;
    jmp L1 # goto L1; //while

E:
    addl $8,%esp
    popl %ebx
    popl %edi
    popl %esi


# n 24
# v 20
# rit 16
# si 12
# di 8
# y 4
# x 0




