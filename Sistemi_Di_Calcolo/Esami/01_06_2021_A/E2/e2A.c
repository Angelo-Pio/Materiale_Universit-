#include "e2A.h"
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
// inserisci la soluzione qui...

char* load(const char* filename, unsigned* size){

    int fd = open(filename,O_RDONLY);

    if(fd == -1){
        perror("failed to open");
        exit(EXIT_FAILURE);
    }


    *size = lseek(fd,0,SEEK_END);
    printf("%d\t",*size);
    if(*size == -1){
        perror("Lseek error");
        exit(EXIT_FAILURE);
    }
    char* buffer =(char*) malloc(*size*sizeof(char));

    int seek = lseek(fd,0,SEEK_SET);

    if(seek == -1){
        perror("Lseek error");
        exit(EXIT_FAILURE);
    }

    int res = read(fd,buffer,*size);

    if(res == -1){
        perror("Error in readingfile");
        exit(EXIT_FAILURE);
    }

    *size = res;

    close(fd);
    




    

    return buffer;
}
