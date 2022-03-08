// scrivere la soluzione qui...

char *my_strcpy(char *dest, const char *src);
void *my_strcpy_aux(char *dest, const char *src);

char *my_strcpy(char *dest, const char *src){

     my_strcpy_aux(dest,src);
     return dest;
    

}

void *my_strcpy_aux(char *dest, const char *src){

        if(*src == '\0'){
            *dest = '\0';
            return dest;
        }

        *dest = *src;
        return my_strcpy_aux(dest+1,src+1);

}