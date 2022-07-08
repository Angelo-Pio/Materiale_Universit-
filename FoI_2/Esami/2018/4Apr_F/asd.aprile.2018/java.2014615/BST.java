import java.util.LinkedList;

public class BST {

    private BinNode root;

    public BST() {
        this.root = null;
    }

    public BinNode getRoot() {
        return root;
    }

    public void print(BinNode t, int level, char pos) {
        if (t == null)
            return;
        for (int i = 0; i < level - 1; i++) {
            System.out.print("   ");
        }

        if (level > 0) {
            System.out.print(" " + pos + ":--");
        }

        System.out.println(t.getKey());

        print(t.getLeft(), level + 1, 'l');
        print(t.getRight(), level + 1, 'r');
    }

    public void BST_print() {
        if (root != null)
            print(this.root, 0, ' ');
    }

    public BinNode BST_insert(int k) {

        if (root == null) {
            root = new BinNode(k);
            return root;
        }
        BinNode rif = null;
        BST_insert_aux(root, rif , k);
        return rif;

    }

   

    private void BST_insert_aux(BinNode node, BinNode rif , int k) {

        if(k == node.getKey() ){
            rif = node;
        }
        BinNode l = node.getLeft();
        BinNode r = node.getRight();
        if(k < node.getKey()){
            if(l != null){
                BST_insert_aux(l, rif, k);
            }else{
                BinNode res = new BinNode(k);
                rif= res;
                node.setLeft(res);
                return;
            }
            
        }
        if(k > node.getKey()){
            if(r!= null){
                BST_insert_aux(r,rif,k);
            }else{
                
                BinNode res = new BinNode(k);
                rif= res;
                node.setRight(res);
                return;
            }
        }
     

    }

    public int isBST() {

        if(root == null){
            return 0;
        }

        LinkedList<Integer> l = new LinkedList<>();
        return isBST_aux(root,l);

    }

    private int isBST_aux(BinNode node, LinkedList<Integer> list) {

        if(node == null){
            return 1;
        }
        BinNode l = node.getLeft();
        BinNode r = node.getRight();
        
        if(compare(node,list) == 0){
            return 0;
        }

        LinkedList<Integer> i_list = new LinkedList<>();
        i_list.addAll(list);
        
        if(l!= null) i_list.add(l.getKey());

        LinkedList<Integer> j_list = new LinkedList<>();
        j_list.addAll(list);
        
        if(r!= null)j_list.add(r.getKey());

        int i = isBST_aux(l,i_list);
        int j = isBST_aux(r,j_list);

        return i == 0 || j == 0 ? 1 : 0;


    }

    private int compare(BinNode node, LinkedList<Integer> list) {
        
        BinNode l = node.getLeft();
        BinNode r = node.getRight();
        
        if(l != null){
            for (Integer key : list) {
                if(l.getKey() > key) return 0;
            }
        }
        if(r != null){
            for (Integer key : list) {
                if(r.getKey() < key) return 0;
            }
        }
        
        return 1;
        
        
    }
    
    public int isBalanced() {
        
        if(root == null){
            return 0;
        }
        return isBalanced_aux(root);
    }
    
    public int altezza(BinNode node){
        if(node == null){
            return 0;
        }else{
            
            int l = 0, r = 0;
            BinNode left = node.getLeft();
            BinNode right = node.getRight();
            
            if(left!= null) l = altezza(node.getLeft());

            if(right!= null) r = altezza(node.getRight());
            
            int max =  l >= r ? l : r ;
            return max +1 ;
        }


    }

    private int isBalanced_aux(BinNode node) {
    
        if(node == null){
            return 0;
        }

            int lh = altezza(node.getLeft()) ;
            int rh = altezza(node.getRight());
            int diff = lh >= rh ? lh - rh : rh - lh;

            if(diff > 1){
                return 0;
            }

            // viene sommato solo 0 mai 1
        
        int l = isBalanced_aux(node.getLeft());
        int r = isBalanced_aux(node.getRight());

        return l == 0 || r == 0 ? 0 : 1;
    }
    public boolean estFoglia(BinNode node){
        return node.getLeft() == null && node.getRight() == null;
    }
    public boolean hasBothChildren(BinNode node){
        return node.getLeft() != null && node.getRight() != null;
    }
}
