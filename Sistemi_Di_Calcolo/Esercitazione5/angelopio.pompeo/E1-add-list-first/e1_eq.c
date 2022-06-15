// Inserisci qui il C equivalente...
#include <stdlib.h>
#include <stdio.h>
#include "e1.h"

int list_add_first(node_t **l, short elem) {

    int size = sizeof(node_t);
    node_t* p = malloc(size);
    if(p == NULL){return -1;}

    printf(" %d ",size);

    p->elem = elem;
    p->next = *l;

    *l = p;
    return 0;

    
    

}


