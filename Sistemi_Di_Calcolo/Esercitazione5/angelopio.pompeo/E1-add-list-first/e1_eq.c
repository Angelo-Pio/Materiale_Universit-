// Inserisci qui il C equivalente...
#include <stdlib.h>
#include "e1.h"

int list_add_first(node_t **l, short elem) {

    
    node_t* d = *l;
    int b = sizeof(d);
    node_t *a = malloc(b);

    if(a == NULL) goto E;

    a->elem = elem;
    a->next = d;

    *l = a;

    int a = 0;
    return a;
E:
    a = 1;
    return a;

}


