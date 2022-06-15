// Scrivi la soluzione qui...

void drop_spaces(char* s){

    while(*s != '\0'){

        if(*s == ' ' && *(s+1) != '\0'){

            *s =   *(s+1);
            *(s+1) = ' ';
        }

        s++;

    }
    return;
}