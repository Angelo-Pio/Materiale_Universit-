// Scrivere la soluzione qui
int findSub(const char* s, const char* sub);

int count_substrings(const char* s, const char* sub){

    int count = 0;

    if(*s == '\0' && *s == '\0'){
        return 1;
    }

    for (int i = 0; s[i] != '\0';i++)
    {
        count+= findSub(s+i,sub);
    }
    return count;
}

int findSub(const char* s, const char* sub){

   while (*sub != '\0')
   {
       if(*sub != *s){
           return 0;
       }

        sub++;
        s++;

   }

   return 1;
   


}

