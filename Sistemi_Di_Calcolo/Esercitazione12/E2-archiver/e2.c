#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "e2.h"



// inserire la soluzione qui...
void archiver(const char* archive, const char** files, int n){

    
    // Crea file e nominalo archive con permessi r-w per host e r per 

    int fd = open(archive,O_WRONLY | O_CREAT | O_TRUNC,0644);
    assert(fd!=-1);

    char* str = "dimensione in byte | contenuto del campo\n";
    char* padding = "------------------------------------------------------\n";
    write(fd,str,strlen(str));
    write(fd,padding,strlen(padding));

    for (int i = 0; i < n; i++)
    {
        char* file_path;
        strncpy(file_path,files[i],strlen(files[i])) ; // prendi un file
        int fd_0 = open(file_path,O_WRONLY | O_CREAT | O_TRUNC); //aprilo
        assert(fd_0!=-1);

        int size = lseek(fd_0,0,SEEK_END);

        char* format = strcat("256                | ",file_path);

        write(fd,format+'\n',strlen(format));

        char* format2;
        sprintf(format2,"8                | %d",size);

        write(fd,format2+'\n',strlen(format2));

        char* format3;
        read(fd_0,format3,size);
        write(fd,format3+'\n',strlen(format3));




        write(fd,padding,strlen(padding));
        close(fd_0); // chiudiilo e passa al prossimo
    }
    
    close(fd);

}