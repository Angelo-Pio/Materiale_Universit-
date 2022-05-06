#include "e2.h"

int main(int argc, char const *argv[])
{
    int max = 18;
    int v[]= {12,23,21,2,32,67,1,3,43,1,32,76,34,12,1,112,56,34};
    

    for (int k = 0; k < max; k++)
    {
        printf("%d-",v[k]);
    }

    puts("\n");

    printf("Start sorting...\n");
    printf("-----------------------------------\n");
    
    sort(v,max);

    printf("-----------------------------------\n");
    
    for (int k = 0; k < max; k++)
    {
        printf("v[%d] = %d \n",k,v[k]);
    }

    puts("\n");
    return 0;
}
