#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "e2.h"

void check_error(int id , char* str){
    if(id == -1){
        perror(strcat("Error",str));
        exit(EXIT_FAILURE);
    }
    return;
}

// inserire la soluzione qui...
void archiver(const char* archive, const char** files, int n){

    int fd = open(archive, O_CREAT | O_TRUNC | O_WRONLY, 0640);
    check_error(fd,"Open archive");
    
    char filename[256];

    for (int i = 0; i < n; i++)
    {
        strcpy(filename,files[i]);
        //  Apri file
        int od = open(filename,O_RDONLY);
        check_error(od,"Open file");

        //Ottieni dimensione file
        long size = lseek(od,0,SEEK_END);
        check_error(size,"Lseek 1");

        // Ristabilisci il puntatore
        int ld = lseek(od,0,SEEK_SET);
        check_error(ld,"Lseek 2 ");

        int res =write(fd,filename,256);
        check_error(res,"Write filename");


        res =write(fd,&size,sizeof(size));
        check_error(res,"Write size filename");

        // Write file
        
        ssize_t r;
        char buff[2048];
        for (;;)
        {
            r = read(od,buff,2048);
            check_error(res,"Read file");

            if(r== 0) break;

            r = write(fd,buff,r);
            check_error(r,"Write file");
        }
        




        res = close(od);
        check_error(res,"Close file");
    }

    int res = close(fd);
    check_error(res,"Close archive");
    

  

}