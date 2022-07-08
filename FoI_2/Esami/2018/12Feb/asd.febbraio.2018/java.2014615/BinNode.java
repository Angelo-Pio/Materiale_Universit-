    public class BinNode{
        private String key;
        private int cont;
        private BinNode left;
        private BinNode right;

        public BinNode(String key) {
            this.key = key;
            cont=1;
            this.left = null;
            this.right = null;
        }
        
        public BinNode getLeft(){
        	return left;
        }

        public BinNode getRight(){
        	return right;
        }
        
        public BinNode setLeft(BinNode n){
        	left = n;
        	return left;
        }

        public BinNode setRight(BinNode n){
        	right = n;
        	return right;
        }
        
        public String getKey(){
        	return key;
        }

        public int getCont(){
            return cont;
        }

        public void setCont(int c){
            cont=c;
        }

        public void incrementaCont(){
            cont++;
        }

    }
