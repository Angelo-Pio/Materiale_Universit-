#include <stdlib.h>
#include <stdio.h>
// inserisci la soluzione qui...
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <fcntl.h>
#include "e2B.h"


void make_files(int n, void (*f)(int i, char name[64], char buf[256]))
{

    for (int j = 0; j < n; j++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Error process");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {

            char name[64];
            char buf[256];
            f(j,name,buf);

            int fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0664);
            if (fd == -1)
            {
                perror("Error open");
                exit(EXIT_FAILURE);
            }

            int res = write(fd, buf, 256);
            if (res == -1)
            {
                perror("Error write");
                exit(EXIT_FAILURE);
            }
            return;
        }

        int status;
        int r = wait(&status);
        if (r == -1)
        {
            perror("Error wait");
            exit(EXIT_FAILURE);
        }
    }
}