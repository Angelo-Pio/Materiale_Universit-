public class alg {
    public static void main(String[] args) {
        process("55555");
    }

    static void process(String s) {
        process("", s);
    }

    static void process(String prefix, String s) {
        int n = s.length();
        if (n == 0)
            System.out.println(prefix);
        else
            for (int i = 0; i < n; i++)
                process(prefix + s.charAt(i), s.substring(0, i) + s.substring(i + 1, n));
    }
}
