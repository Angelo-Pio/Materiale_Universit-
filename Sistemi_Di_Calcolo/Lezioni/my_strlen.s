
.globl my_strlen

my_strlen:

    xorl %eax,%eax # Azzera eax a = counter
    movl 4(%esp),%ecx

    L:  

        cmpb $0, (%ecx)
        je E

        incl %eax
        incl %ecx # un puntatore è un numero
        jmp L
        ret
    E: 
        ret
# Funzione C

#  unsigned my_strlen(const char* s){
#      unsigned cnt = 0;
#      while (*s++) cnt++; C avanzato s != 0 e poi s++
#      return cnt;
#  }


# Forma Equivalente

#    unsigned a = 0;
#    L: 
#        if(*s == '\0') goto E;
#            a++;
#            s++;
#            goto L
#
#        return a
#    E:  