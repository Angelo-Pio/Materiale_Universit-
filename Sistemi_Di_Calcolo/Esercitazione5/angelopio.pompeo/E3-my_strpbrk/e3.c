#include "e3.h"
#include <stdlib.h>
// La funzione my_strpbrk(s1, s2) deve restituire il puntatore alla prima 
// occorrenza in `s1` di un qualsiasi carattere presente nella stringa `s2` 
// oppure `NULL` se alcun carattere di s2 appare in `s1` prima che `s1` 
// stessa termini.

// scrivere la soluzione qui...
char *my_strpbrk(const char *s1, const char *s2){

    char* s = (char*)s1;

    while (*s != '\0')
    {
        char* t = (char*)s2;
        while(*t != '\0')
        {
            if(*s == *t){
                return (char *)s;
            }
            t+=1;
        }
        s+=1;
    }

    return NULL;
    

}