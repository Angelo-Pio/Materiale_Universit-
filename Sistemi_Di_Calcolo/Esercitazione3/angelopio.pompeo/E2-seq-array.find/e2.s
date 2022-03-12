# scrivere la soluzione qui...

.globl find

find:       # int find(int* v, int n, int x) {

    movl $0,%ecx        #  i = 0
    movl 4(%esp),%edx   # d = v

S:
    

              # ++i
    incl %ecx 
    cmpl 8(%esp),%ecx   # i < n 
    jge T

        movl (%edx,%ecx,4),%eax # a = v[i]
        cmpl 12(%esp),%eax  # a == x
        je E                # goto E
    
    
    jmp S     # loop



E: 
    movl $1, %eax
    ret

T: 
    movl $0, %eax
    ret