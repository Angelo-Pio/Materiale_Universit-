.globl swap
swap:                   # void swap(char* x, char* y){

    # un puntatore è un intero perciò si muove sempre con movl

    movl 4(%esp),%ecx   #     char* c = x;
    movl 8(%esp),%edx   #     char* d = y;
    movb (%ecx),%al     #     char al = *c;
    movb (%edx), %ah    #     char ah = *d,
    movb %ah,(%ecx)     #     *c = ah ;
    movb %al,(%edx)     #     *d = al;

    