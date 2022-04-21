public class BST<V> {



    private class Node<V>{
        protected int key;
        protected V value;
        
        protected Node<V> left;
        protected Node<V> right;
        
        public Node(int key, V value) {
            this.key = key;
            this.value = value;
        }

        public int getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }

        public void setValue(V value) {
            this.value = value;
        }
        
        
        
        
        
        
    }
    
    public Node<V> radix;
    
    public BST(int key, V value) {
        radix = new Node<>(key,value);
    }

    
    private void insert(Node<V> radix, int k, V v) {
        
        if(radix.getKey() == k){
            radix.setValue(v);
        }
        
        if(k < radix.getKey()){
            
            if(radix.left == null){
                radix.left = new Node<>(k,v);
            }else{
                insert(radix.left,k,v);
            }
            
        }else{
            if(radix.right == null){
                radix.right = new Node<>(k,v);
            }else{
                insert(radix.right,k,v);
            }
        }
        
    }
    
    public void insert(int k, V v) {
            
        if(radix == null){
            radix = new Node(k, v);
        }else{
            insert(radix,k,v);
        }
        
        
        
    }

    public V find(int k) {
        
        if(radix == null)
             return null;
        else
            return findNode(radix,k).getValue();
        
    }

    
    public Node<V> findMin(Node<V> r){
        
        if(r.left == null){
            return r ;
        }
        return findMin(r.left);
        
    }
    
    public int findMin() {
        
        if(radix == null){
            return -1;
        }else{
           return findMin(radix).getKey(); 
        }
        
    }
    
    private void removeMin(Node<V> r){
        return;
    }
    
    public void removeMin() {
        
        if(radix == null){
            return;
        }else{
            removeMin(radix);
        }
        
        
    }

    public void remove(int k) {
        return;
    }

    private void print(Node<V> t, int level) {

        if (t == null)
            return;

        for (int i = 0; i < level - 1; i++) {
            System.out.print("   ");
        }

        if (level > 0) {
            System.out.print(" |--");
        }

        System.out.println(t.key);

        print(t.left, level + 1);
        print(t.right, level + 1);
    }

    void print(){
        print(this.radix, 0);
    }

    int predecessor(Node<V> n){
        
        //Se ha figlio sinistro cerca lì dentro il minimo
        if(n.left != null){
            return findMax(n.left).getKey();
        }
       
        
        
        
    }
    
    
    private Node<V> findMax(Node<V> r){
        
        if(r.right == null){
            return r ;
        }
        return findMin(r.right);
        
    }
    
    
    int predecessor(int k) {
        
        predecessor(findNode(radix, k));

    }
    
    protected Node<V> findNode(Node<V> rad , int k){
        
        if( rad == null){
            return rad;
        }
        
        if(rad.getKey() == k){
            return rad;
        }

        if( k < rad.getKey()){
            return findNode(rad.left,k);
        }

        if( k > rad.getKey()){
            return findNode(rad.right,k);
        }
        
         return null;   
    }
    
    protected boolean estFoglia(Node<V> rad){
        return rad.left == null && rad.right == null;
    }

}
