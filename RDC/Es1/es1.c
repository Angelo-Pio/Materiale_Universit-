#include <stdio.h>

int main(int argc, char const *argv[])
{
    int x;
    int sum = 0;

    for (int i = 0; i < 3; i++)
    {   
        printf("insert number ");
        scanf("%d",&x);
        sum += x;
    }
    sum /= 3;
    
    printf("sum equals: %d",sum);
    return sum;
}
