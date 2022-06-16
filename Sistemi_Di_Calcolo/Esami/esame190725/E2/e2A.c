#include "e2A.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include <stdlib.h>
// inserisci la soluzione qui...

int contains(char *s, char c, int n)
{
    int* buff = (int*)malloc(n*sizeof(int));
    int len = strlen(s);
    int m = len / n;

    pid_t pid;
    int j = 0;

    int presente = 0;

    if (m * n < len)
    {
        for (int i = n * m; i < len; i++)
        {
            if (s[i] == c)
                presente = 1;
        }

    }
    if(presente) return 1;

    for (j; j < n; j++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            presente = 0;

            for (int k = j * m; k < (j + 1) * m; k++)
            {
                if (s[k] == c)
                    presente = 1;
            }
            if (presente)
            {
                _exit(1);
            }
            else
            {
                _exit(0);
            }
        }

        int status;

        pid = wait(&status);

        if (pid == -1)
        {
            perror("error");
            exit(EXIT_FAILURE);
        }
        int res = WEXITSTATUS(status);
        if(res == 1) return 1;

    }

    return 0;



   
}