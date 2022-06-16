# inserire la soluzione qui...

.globl most_freq_char

most_freq_char: # int most_freq_char(const char* s, int* map) {


    pushl %edi
    pushl %esi
    pushl %ebx
    subl $8,%esp




    movl 28(%esp),%esi  # int* si = map;
    movl 24(%esp),%edi  # const char* di = s;


    movl %esi,(%esp)
    movl $256,4(%esp)
    call clear # clear(si, 256);


    movl $0,%ecx # int c = 0 , a = 0;
    movl $0,%eax

L:  

    movb (%edi),%dl
    cmpb $0,%dl # if(*di == 0) goto L1;
    je L1

    movsbl %dl,%edx # int d = *di;
    # int d = *di;
    # d = si[d]++;

    incl (%esi,%edx,4)      # d = si[d]++;

    incl %edi # di++;
    jmp L # goto L;

L1:
    
    cmpl $256,%ecx # if(c>= 256) goto E;
    jge E
    
        movl (%esi,%ecx,4),%edx
        cmpl (%esi,%eax,4),%edx        # if (si[c] > si[a]) a = c;
        cmovgl %ecx,%eax

    incl %ecx # c++;
    jmp L1 # goto L1;

E:    
    addl $8,%esp
    popl %ebx
    popl %esi
    popl %edi
    ret
# map 28
# s 24
# rit 20
# di 16
# si 12
# b 8
# y 4
# x 0    
