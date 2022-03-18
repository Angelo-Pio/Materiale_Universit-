// Scrivi la soluzione qui...

void drop_spaces(char* s){

    char *res = s;
    int j = 0;
    int i = 0;
    while(s[i] != '\0'){

        if(s[i] != ' '){
            res[j] = s[i];
            j++;
        }
        i++;

    }

    res[j] = '\0';



    s = res;
    return;


}