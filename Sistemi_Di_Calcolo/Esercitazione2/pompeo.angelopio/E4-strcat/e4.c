// scrivere la soluzione qui...

// char *my_strcat(char *dest, const char *src);

char *my_strcat(char *dest, const char *src){

    char* res = dest;

    int i = 0;


    while (dest[i] != '\0')
    {
        i++;
    }



    int j = 0;

    while ( src[j] != '\0')
    {
        dest[i+j] = src[j];
        j++;
    }
    
    dest[i+j] = '\0';
    return dest;
    

    


}
