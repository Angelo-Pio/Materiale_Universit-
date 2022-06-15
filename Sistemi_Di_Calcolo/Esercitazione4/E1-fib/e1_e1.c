int fib(int n) {

    int b = n;
    int a = 0;

    if(b < 2){
        goto E;
    }

    int si = fib(b-1); 
    int di = fib(b-2); 

    return di + si;

    E: 
        a = 1;
        return a;
}