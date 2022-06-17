#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "e2A.h"
// inserisci la soluzione qui...

void run(int* v, int n, int (*f)(int i)){

    for(int i = 0; i < n ; i++){

        pid_t pid = fork();
        if(pid == -1){
            perror("Error");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            _exit(f(i));
        }

        int status;
        int res = wait(&status);
        if(res == -1){
            perror("Error wait");
            exit(EXIT_FAILURE);
        }

        v[i] = WEXITSTATUS(status);

    }
}
