// Scrivere il C equivalente qui...
#include "e2.h"
#include <stdlib.h>


void list_concat(node_t **l1, node_t *l2) {

    node_t *a = *l1;
    if( a == NULL) goto L;
    
R:  

    if(a->next == NULL) goto E;
    a = a->next;    

    goto R;

L: 
    a = l2;
    return ;

E:
    a->next = l2;
    return ;
}