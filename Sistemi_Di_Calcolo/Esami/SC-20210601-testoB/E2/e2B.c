#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "e2B.h"


// inserisci la soluzione qui...
off_t searchfile(char* filename, char c){

    int fd = open(filename,O_RDONLY);

    if(fd == -1){
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    int size = lseek(fd,0,SEEK_END);
    if(size == -1){
        perror("Error lseek 1");
        exit(EXIT_FAILURE);
    }

    int res = lseek(fd,0,SEEK_SET);

    if(res == -1){
        perror("Error lseek 2");
        exit(EXIT_FAILURE);
    }

    int off = 0;

    char buff[1];

    for (int i = 0; i < size; i++)
    {   

        res = read(fd,buff,1);
        printf("%s-",buff);

        if(res == -1){
            perror("Error read file");
            exit(EXIT_FAILURE);
        }

        if(*buff == c){
            return off;
        }


        off++;


    }

    close(fd);
    return -1;
    


}