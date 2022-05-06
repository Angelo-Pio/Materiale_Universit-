#include "e2.h"

int i, max;


static void do_sort(int *v, int n) {

// Stampe
    int j;
    
    
    
    for (i=0; i<n; ++i)
        kill(getpid(),SIGUSR1);
        for (j=1; j<n; ++j)
            if (v[j-1] > v[j]) {
                int tmp = v[j-1];
                v[j-1] = v[j];
                v[j] = tmp;
            }
}

void handler(int signum){
    printf("%.2f%% \n",percetage(i,max));
}

void sort(int *v, int n) {

    // completare con gestione segnali...
    max = n;
    struct sigaction act = { 0};
    
    act.sa_handler = handler;

    int ret = sigaction(SIGUSR1,&act,NULL);

    if(ret == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    
    do_sort(v, n);


}

float percetage(int i , int max){
    return 100.0*i/max;
}