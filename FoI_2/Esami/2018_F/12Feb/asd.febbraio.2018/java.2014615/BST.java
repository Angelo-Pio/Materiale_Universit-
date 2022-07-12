public class BST{

    private BinNode root;

    public BST() {
        this.root = null;
    }

    public BinNode insert(String k) {

        if(root == null){

            root = new BinNode(k);
            return root;
        }
        String s = k.toUpperCase();
        return insert_aux(root,s);
    }

    public BinNode insert_aux(BinNode node, String k){

        int comp = k.compareTo(node.getKey());
        if(comp == 0){
            node.incrementaCont();
            return node;
        }
        if( comp < 0){
            BinNode l = node.getLeft();
            if( l == null){
                return node.setLeft(new BinNode(k));
            }else{
                return insert_aux(l, k);
            }
        }
        if(comp > 0){
            BinNode r = node.getRight();
            if( r == null){
                return node.setRight(new BinNode(k));
            }else{
                return insert_aux(r, k);
            }

        }
        return node;
    }

    public int find(String k) {
        return find_aux(root,k.toUpperCase());

    }

    public int find_aux(BinNode node, String k){
        int comp = k.compareTo(node.getKey());
        if(comp == 0){
            return node.getCont();
        }
        if( comp < 0){
            BinNode l = node.getLeft();
            if( l == null){
                return 0;
            }else{
                return find_aux(l, k);
            }
        }
        if(comp > 0){
            BinNode r = node.getRight();
            if( r == null){
                return 0;
            }else{
                return find_aux(r, k);
            }

        }
        return 0;
    }

    private void print(BinNode t, int level, char pos) {
        /* MODIFICABILE */
        if (t==null) return;
        for (int i = 0; i < level - 1; i++) {
            System.out.print("   ");
        }

        if (level > 0) {
            System.out.print(" "+pos+":--");
        }

        System.out.println("key: " + t.getKey() + "     occorrenze: " + t.getCont());

        print(t.getLeft(), level + 1,'l');
        print(t.getRight(), level + 1,'r');
    }

    public void BST_print(){
        if (root!=null)
            print(this.root, 0,' ');
    }

    public String mostFrequentString(){

        if(root == null) return "";

        BinNode buf = new BinNode("");
        buf.setCont(-1);
        return mostFrequentString_aux(root,buf);
    }

    public String mostFrequentString_aux(BinNode node, BinNode buf){

        BinNode l = node.getLeft();
        BinNode r = node.getRight();


        if(node.getCont() >= buf.getCont()){
            buf = node;
            
        }
        
        if( l != null)
        {
            mostFrequentString_aux(l, buf);
        }
        if( r != null){
            mostFrequentString_aux(r, buf);
        }
        
        return buf.getKey();
        


    }

    public int heigth(BinNode node){
        if(node == null) return 0;
        else{

            
            BinNode left = node.getLeft();
            BinNode right = node.getRight();
            int l= 0,r = 0;
            if(left != null){
                
                l = heigth(node.getLeft());
            }
            if(right != null){
                
                r = heigth(node.getRight());
            }
            
            int max = l >= r ? l : r ;
            return max +1 ;
        }
    }
    
    public int isBalanced() {
        
        if(root == null){
            return -1;
        }
        return isBalanced_aux(root);

    }

    public int isBalanced_aux(BinNode node){
        BinNode l = node.getLeft();
        BinNode r = node.getRight();
        
        if (l == null && r == null){
            return 1;
        }
        int lh = heigth(l) ;
        int rh = heigth(r);
        int max = lh >= rh ? lh-rh : rh-lh;
        
        if(max > 1 ){
            return 0;
        }

        int left = isBalanced_aux(l);
        int right = isBalanced_aux(r);

        return left == 1 || right == 1 ? 1 : 0;

    }


}
