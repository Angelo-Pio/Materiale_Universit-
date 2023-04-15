#include <stdio.h>

int main(int argc, char const *argv[])
{
    int arr[3] = {1,2,3};
    int *p = arr;
    printf("%d\n",*(p+1));
    p = &arr[2];
    printf("%d\n",*(p-1));


    return 0;
}
