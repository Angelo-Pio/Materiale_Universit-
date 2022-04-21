#include "e1.h"

int count_digits(const char *s) {
	int a = 0;

    const char* c = s;
L:
    if(*c == 0){goto E;}
		if (*c >= 48 && *c <= 57) a++;
		c = c+1;
        goto L;
E:	
	return a;
}