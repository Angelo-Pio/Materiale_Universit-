// inserire il C equivalente qui...
#include "e1A.h"

int count_tokens(char* str, const char* sep) {
    int a = 0;
    char* b = str;
    const char* si = sep;

    char * c = strtok(b,si);

L:
    if(c == NULL) goto E;

        a++;
        b = 0;
        c = strtok(b,si);

    goto L;

E:

	return a;
}