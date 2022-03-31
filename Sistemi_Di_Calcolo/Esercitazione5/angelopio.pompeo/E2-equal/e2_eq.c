// Inserisci qui il C equivalente...
#include "e2.h"

int list_equal(const node_t *l1, const node_t *l2) {

    const node_t* c = l1;
    const node_t* d = l2;

L:
    if(c == 0) goto E;
    if(d == 0) goto E;

    if(c->elem != d->elem) goto F;
    c = c->next;
    d = d->next;
    goto L;

F:
    int a = 0;
    return a;
E:
    a = (c == d) ? 1 : 0;    
    return a;


}