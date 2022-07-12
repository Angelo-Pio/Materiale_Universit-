public class test{

    
    public static void main(String[] args) {
        int a[] = {9,8,7,6,5,4,3};
        ordina(a,0);
        
    }
    
    static int[] infila(int i, int[] a, int c) {
        
        int x = a[i]; int j = i+1;
        if(j == a.length || x <= a[j]) return a;
        a[i] = a[j]; a[j] = x;
        c++;
        if(c== 1) System.out.println("i:" + i + "\n");
        System.out.println("inf" + c);
        return infila(j, a,c);
    }
    
    // assumere a.length > 0
    static int[] ordina(int[] a) {
        return ordina(a, 0);
    }
    static int[] ordina(int[] a, int i) {
        if(i+1 == a.length) return a;
        System.out.println("o");
        return infila(i, ordina(a, i+1),0);
    }
}
