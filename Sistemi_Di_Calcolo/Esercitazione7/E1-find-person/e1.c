// Scrivi la soluzione qui...
#include "e1.h"

#include <string.h>

int compar(const void* a , const void* b){
    person_t x = *(person_t*)a;
    person_t y = *(person_t*)b;

    char* s1 = x.name;
    char* s2 = y.name;

    return strcmp(s1,s2);
}

void sort_people(person_t p[], size_t n){

   qsort(p,n,sizeof(person_t),compar); 

}


person_t *find_person(char *key, person_t sorted[], size_t n){

    person_t per ;
    per.name = key;
    return bsearch(&per,sorted,n,sizeof(person_t),compar);

}