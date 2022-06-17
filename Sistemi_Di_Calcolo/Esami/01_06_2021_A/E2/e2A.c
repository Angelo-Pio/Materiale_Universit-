#include "e2A.h"
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// inserisci la soluzione qui...

void check_id(int id, char* str){
    if(id == -1){
        str = strcat("Error",str);
        perror(str);
        exit(EXIT_FAILURE);
    }
}

char* load(const char* filename, unsigned* size){

    int fd = open(filename,O_RDONLY);
    check_id(fd,"Open");

        int size_f = lseek(fd,0,SEEK_END);
        check_id(size_f,"lseek 1");

        int res = lseek(fd,0,SEEK_SET);
        check_id(res,"lseek 2");

        char* buffer = (char*)malloc(size_f * sizeof(char));
        res = read(fd,buffer,size_f);
        check_id(res,"Read");
        *size = res;
        

    res = close(fd);
    check_id(res,"Close");
    return buffer;
}
