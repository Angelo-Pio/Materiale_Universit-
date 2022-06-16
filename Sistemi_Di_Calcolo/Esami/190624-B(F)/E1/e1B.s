# inserire la soluzione qui...
.globl has_duplicates

has_duplicates: #int has_duplicates(short* v, unsigned n) {

    pushl %esi
    pushl %ebx

    movl 12(%esp),%esi  # short* si = v;
    movl $0,%ecx # unsigned c = 0;
    leal 1(%ecx),%edx # unsigned d = c+1;
    movl $0,%eax # int a = 0;

L:
    cmpl 16(%esp),%ecx # if(c >= n) goto E;
    jge E        
    leal 1(%ecx),%edx # d = c+1;

L1:        

    cmpl 16(%esp),%edx # if(d >= n ) goto L2;
    jge L2

        movw (%esi,%ecx,2),%bx
        cmpw (%esi,%edx,2),%bx #if (si[c] == si[d]) goto E0;
        je E0
        
    incl %edx #d+=1;
    jmp L1 # goto L1;
L2:
    incl %ecx # c++;
    jmp L #goto L;
E0:
    movl $1,%eax # a = 1;

E:       
    popl %ebx
    popl %edi
    ret 


# n 12
# v 8
#rit 4
# esi 0







