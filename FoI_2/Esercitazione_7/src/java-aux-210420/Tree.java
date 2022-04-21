public class Tree {

    private int key;
    private Tree left;
    private Tree right;

    public Tree(int key) {
        this.key = key;
    }

    public static Tree build_1() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);
        Tree n7 = new Tree(7);
        Tree n15 = new Tree(15);

        n6.left = n3;
        n6.right = n12;

        n3.left = n1;
        n3.right = n5;

        n12.left = n7;
        n12.right = n15;

        return n6;
    }

    public static Tree build_2() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);
        Tree n7 = new Tree(7);
        Tree n15 = new Tree(15);

        n6.right = n3;
        n6.left = n12;

        n3.left = n1;
        n3.right = n5;

        n12.left = n7;
        n12.right = n15;

        return n6;
    }

    public static Tree build_3() {

        Tree n6 = new Tree(6);
        Tree n3 = new Tree(3);
        Tree n12 = new Tree(12);
        Tree n1 = new Tree(1);
        Tree n5 = new Tree(5);

        n6.left = n3;

        n3.left = n1;
        n3.right = n5;

        n5.right = n12;

        return n6;
    }

    public boolean isBST() {
    
        if(this.left == null && this.right == null){
            return true;
        }
        
        if(this.left.key > this.key){
            return false;
        }
        
        if(this.right.key < this.key){
            return false;
        }
        
        return left.isBST() && right.isBST();
        
        
    }

    public boolean isBalanced() {
        
        if(this.left == null && this.right == null){
            return true;
        }
        
        if(this.left.key > this.key){
            return false;
        }
        
        if(this.right.key < this.key){
            return false;
        }
        
        int b = balFactor(this.left,this.right);
        
        if( b < -1 || b > 1  ){
            return false;
        }
        
        
        return left.isBalanced() && right.isBalanced();
        
        
        
        
    }

    public boolean isAVL() {
        return true;
    }
    
    protected int depth(Tree a){
        
        if(a == null){
            return 0;
        }else{
        
            int l = depth(a.left);
            int r = depth(a.right);

            if(l > r) { return l+1;}
            else{ return r+1;}
        }
        
    }

    protected int balFactor(Tree l, Tree r){
        
        return depth(l) - r.depth(r);
    
    }

}
