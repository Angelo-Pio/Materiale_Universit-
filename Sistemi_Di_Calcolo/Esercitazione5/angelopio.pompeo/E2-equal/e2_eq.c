// Inserisci qui il C equivalente...
#include "e2.h"

int list_equal(const node_t *l1, const node_t *l2) {

    const node_t* si = l1;
    const node_t* di = l2;

    int a = 0;

L:  

    if(si == 0){
        goto E1;
    }
        if(di == 0){
            goto E1;
        }

    short c = l1->elem;
    short d = l2->elem;

    if(c != d){
        goto E;
    }

    si = si->next;
    di = di->next;
    goto L;


E1:

    if(si == 0){
        a = si == di ? 1 : 0 ;
    }

E:
    return a;



}