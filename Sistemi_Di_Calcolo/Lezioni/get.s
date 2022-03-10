.globl get    

get:   # short get(short *v, unsigned n , unsigned i)
    
    movl 12(%esp),%ecx            #     unsigned c = i;
    movl 4(%esp), %edx            #     short *d = v;
         
    compl 8(%esp),%ecx           ;#     if(c>=n) 
    jae E                         #     goto E
    movw (%edx, %ecx ,2 ), %eax   #     return d[c];  (d + c) 
    ret                           # 

E:                                # E: 
    movw $-1,%ax                  #     short ax = -1;
    ret                           #     return -1;