#include "e1.h"

void bubble_sort(short *v, unsigned n)
{
    unsigned i, again;

L:
    again = 0;
    i = 1;

E:
    if (i >= n)
    {
        goto L1;
    }
        if (v[i - 1] > v[i])
        {
            swap(&v[i - 1], &v[i]);
            again = 1;
        }

    ++i;
    goto E;
L1:

    if (again)
    {
        goto L;
    }

    return;
}
