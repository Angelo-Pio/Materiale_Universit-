#include <string.h>
#include <stdio.h>

void trim(char* string, char* substring );

int main(int argc, char const *argv[])
{
    
    char* string ;
    char* substring ;

    printf("Insert string to be processed: \n");
    
    scanf("%s",string);
    
    printf("Insert substring: \n");

    scanf("%s",substring);

    trim(string,substring);


    printf("Result: %s\n", string);


    return 0;
}

void trim(char* string, char* substring ){

    char* res;
    char* buf;

    for (int count = 0; string[count] != "\0" ; count++)
    {
        buf[count] = string[count];


        res[count] = string[count];



        
    }
    



}