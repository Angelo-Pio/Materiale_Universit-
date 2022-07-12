
public class BST {

    private BinNode root;
    private int size;
    // Pi greco: Math.PI

    public BST() {
        /* NON MODIFICARE */
        this.root = null;
        size = 0;
    }

    private double getRadius(double x, double y) {
        return Math.sqrt(x * x + y * y);
    }

    private double getRadius(BinNode t) {
        return getRadius(t.getCoordinates()[0], t.getCoordinates()[1]);
    }

    private double getPhase(double x, double y) {
        return Math.atan2(y, x);
    }

    private double getPhase(BinNode t) {
        return getPhase(t.getCoordinates()[0], t.getCoordinates()[1]);
    }

    private int compare(double[] node, double[] next) {

        double node_r = getRadius(node[0], node[1]);
        double next_r = getRadius(next[0], next[1]);
        int answ;

        if (node[0] == next[0] && node[1] == next[1])
            return 0;
        else {

            if (node_r == next_r) {

                return getPhase(node[0], node[1]) > getPhase(next[0], next[1]) ? 1 : -1;

            } else {
                return node_r > next_r ? 1 : -1;
            }
        }
    }

    public BinNode BST_insert(double x, double y) {

        if (root == null) {
            root = new BinNode(x, y);
            return root;
        }
        return BST_insert(root, x, y);

    }

    public BinNode BST_insert(BinNode node, double x, double y) {

        BinNode l = node.getLeft();
        BinNode r = node.getRight();

        double[] coor = new double[2];
        coor[0] = x;
        coor[1] = y;
        int comparator = compare(coor,node.getCoordinates());
        if (comparator == 0) {

            return null;
        } else if (comparator == 1) {

            if (r != null) {
                return BST_insert(r, x, y);
            } else {
                
                return node.setRight(new BinNode(x,y));
            }
        } else {
            
            if (l != null) {
                return BST_insert(l, x, y);
            } else {
                return node.setLeft(new BinNode(x,y));
            }

        }
    }

    

    private void print(BinNode t, int level, char pos) {
        /* NODIFICABILE */
        if (t == null)
            return;
        for (int i = 0; i < level - 1; i++) {
            System.out.print("   ");
        }

        if (level > 0) {
            System.out.print(" " + pos + ":--");
        }

        System.out.println("coordinate: (" + t.getCoordinates()[0] + "," + t.getCoordinates()[1] + "); radius="
                + getRadius(t) + " ; phase=" + getPhase(t));

        print(t.getLeft(), level + 1, 'l');
        print(t.getRight(), level + 1, 'r');
    }

    public void BST_print() {
        /* MODIFICABILE */
        if (root != null)
            print(this.root, 0, ' ');
    }

    public int corona(double r1, double r2) {
        /**** DA IMPLEMENTARE ****/
        return -1; // istruzione aggiunta per permettere la compilazione
    }

    public double maxCorona() {
        /**** DA IMPLEMENTARE ****/
        return -1; // istruzione aggiunta per permettere la compilazione
    }

}
