import org.w3c.dom.Node;

public class BST<V> {

    Node<V> root ;
    
    private class Node<V> {
        int key;
        V value;
        Node<V> sin = null;
        Node<V> des = null;

        public Node(int k, V v){
            this.key = k;
            this.value = v;

        }
        
    }

    public BST(int key, V value) {
        root= new Node<>(key, value);
    }


    public void insert(int k, V v) {
        if(this.root == null){
            root = new Node<V>(k, v);
        }else{
            insert(this.root,k,v);
        }
    }

    private void insert(BST<V>.Node<V> node, int k, V v) {
        if(node.key == k){
            node.value = v;
        }
        if(k < node.key){

            if(hasLeft(node)){
                insert(node.sin, k, v);
            }else{
                node.sin = new Node<V>(k, v);
            }
            
            
        }else{
            
            if(hasRight(node)){
                insert(node.des, k, v);
            }else{
                node.des = new Node<V>(k, v);
            }
        }
    }


    public V find(Node<V> node , int k) {

        // Chiave non presente ritorna il nodo
        if(node.equals(null)){
            return null;
        }
        // Chiave trovata, ritorna il nodo
        if(node.key == k){
            return node.value;
        }
        // Cerca in preordine nell'albero 
        if(node.key < k && hasLeft(node)){
            return find(node.sin,k); 
        }
        else if(node.key > k && hasRight(node)){
            return find(node.des,k); 
        }else{
            return null;
        }

    }
    public V find(int k) {

        V b = find(this.root,k);
        if(b != null){
            return b;
        }else{
            return null;
        }

    }

    private boolean hasLeft(Node<V> node) {
        return node.sin != null;
    }
    
    private boolean hasRight(Node<V> node) {
        return node.des != null;
    }

    public int findMin(Node<V> node) {
        // Chiave non presente ritorna il nodo
        if(!hasLeft(node)){
            return node.key;
        }
        // Cerca in preordine nell'albero 
        else{
            return findMin(node.sin); 
        }
    }    

    public int findMin(){
        if(this.root.equals(null)){
            return -1;
        }else{
            return findMin(this.root);
        }
    }
    
    public void removeMin() {
        
        if(this.root.equals(null)){
            return;
        }else{
            removeMin(this.root);
        }
    }

    private Node<V> removeMin(Node<V> node) {

        if(!hasLeft(node)){
            return node.des;
        }
            node.sin = removeMin(node.sin);
        return node;
    }


    public void remove(int k) {
        if(this.root == null){
            return;
        }
        remove(this.root, k);
    }

    public boolean hasTwoChildren(Node<V> node){
        return 
    }

    private void remove(Node<V> node, int k) {

        


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

        print(t.sin, level + 1);
        print(t.des, level + 1);
    }

    void print(){
        print(this.root, 0);
    }

    int predecessor(int k) {
        return 0;
    }
}
