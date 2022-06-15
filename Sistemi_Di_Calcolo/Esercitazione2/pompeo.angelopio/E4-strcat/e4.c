// scrivere la soluzione qui...

// char *my_strcat(char *dest, const char *src);

char *my_strcat(char *dest, const char *src){

    char *res = dest;

    while(*dest != '\0'){

        dest++;

    }

    while(*src !='\0'){

        *dest =*src;
        src++;
        dest++;
    }

    *dest = '\0';

    return res;


    


}
