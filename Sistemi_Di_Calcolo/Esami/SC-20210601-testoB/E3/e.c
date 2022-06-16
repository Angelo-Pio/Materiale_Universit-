#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

    pid_t first = fork() ;
    pid_t second = fork() ;

    if (first && second )
    {
        printf("%d  ",first && second);
        printf("%d - %d\n",first,second);
        // pid_t third = fork() ;
        if (fork() )
            printf("%d\n",getpid());
            printf("o\n");
    }
}