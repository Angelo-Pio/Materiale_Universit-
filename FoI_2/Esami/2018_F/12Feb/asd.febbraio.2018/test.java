/**
 * test
 */
public class test {

    public static void main(String[] args) {
        int[] a = {4,1,2,12};
        int[] b = new int[4];
        for (int i = 0; i < a.length; i++) {
            b[i] = g(a);
        }
        for (int i = 0; i < b.length; i++) {
            System.out.println(b[i]);
        }
    }

    // assumere a.length > 0
    static int g(int[] a) {
        return g(a, 0, a.length - 1);
    }

    static int g(int[] a, int i, int j) {
        if (i == j)
            return a[i];
        int onefourth = (j + 1 - i) / 4;
        return g(a, i, i + onefourth) + g(a, i + onefourth + 1, j);
    }
}