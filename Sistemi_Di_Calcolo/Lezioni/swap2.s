.globl swap2

swap2:
    
    movl 4(%esp),%ecx
    movl 8(%esp),%edx
    movw (%ecx), %cx
    movw (%edx), %dx
    movl 4(%esp),%eax
    movw %dx,%eax
    movl 8(%esp),%eax
    movw %cx,(%eax) 

    ret





# void swap()short*x, shhort* y){
#     short tmp = *x; 
#     *x = *y;
#     
# }
#
# void swap()short*x, shhort* y){
#     short *c = x;
#     shprt *d = y;
#     short cx = *c; # perdo il valore di c originario 
#     short *dx = *d;
#     short* a = x;
#     *a = dx;
#     a = y;
#     *a = cx;       
# }
    