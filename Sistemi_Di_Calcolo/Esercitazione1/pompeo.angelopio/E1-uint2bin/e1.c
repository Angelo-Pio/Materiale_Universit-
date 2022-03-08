#include <stdio.h>
// Segnature
void uint2bin(unsigned x, char bin[32]);


//funzioni

void uint2bin(unsigned x, char bin[32]){


 
    for (int i = 0; i < 32; i++)
    {
        bin[i] = '0';
    }
    
    
    int i = 31;

    while(x != 0){


        if(x%2 == 1){

            bin[i] = '1';
        }else{

            bin[i] = '0';
        }

        x = x/2;
        
        i -= 1;
    }
    


   



}

