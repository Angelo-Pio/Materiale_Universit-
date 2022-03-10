# void times2(short* p){

.globl times2

times2:

    movl  4(%esp),%eax    #    short *a = p; i puntatori sono numeri, non esistono in assenbly
    movw (%eax),%cx       #    short cx = *a;
    imul $2,%cx           #    cx = cx * 2;
    movw %c,(%eax)        #    *a = cx;
    ret                   #    return
    

