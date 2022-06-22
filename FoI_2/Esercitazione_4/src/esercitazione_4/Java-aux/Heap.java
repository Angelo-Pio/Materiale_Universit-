public class Heap {

    public enum HEAP_TYPE {MAX_HEAP, MIN_HEAP};

    public static class HeapEntry {
        int key;
        int position;
        
        public HeapEntry (int key){
            this.key = key;
        }
        public HeapEntry (int key, int position){
            this.key = key;
            this.position = position;
        }
     
        public void setPosition(int position) {
            this.position = position;
        }

        public int getPosition() {
            return position;
        }

        public int getKey() {
            return key;
        }
    }

    
    HEAP_TYPE type;
    int capacity;
    HeapEntry[] heap ;
    int size = 0;
    
    public Heap(HEAP_TYPE type, int capacity) {
        this.capacity = capacity;
        this.type = type;
        this.size = 0;
        this.heap = new HeapEntry[capacity];
    }
    
    public HeapEntry add(int key) {
        // Implementazione di upheap-bubbling

        // Controlla che ci sia spazio nell'array, nel caso raddoppia
        
        if(size >= capacity){
            increaseHeapCapacity();
        }

        // crea una entry
        HeapEntry e = new HeapEntry(key,size); 
        
        //Inseriscila in fondo all'array 
        heap[size] = e;
        //Rispetta la proprietà di heap-order in base al tipo di heap
        
        
        int i = e.getPosition();
        int j = getParent(i);
        
        upHeap(i, j);
        

        // incrementa la size
        size++;
        return e;
    }

    public void upHeap(int i, int j){
        while(j != -1 && compare(i,j)){
            
            swap(i, j);

            i = j;
            j = getParent(i);
        }
    }

    public void downHeap(int i){

        while (hasLeft(i)) {
            this.print();
            System.out.println("");

            int l = getLeftChild(i);
            int c = l;
            if(hasRight(i)){
                int r = getRightChild(i);
                if(!compare(l, r)){
                    c = r;
                }
            }

            if(compare(i,c)) break;

            swap(i, c);
            i = c;
        }

    }
    
    public int poll() {

        if(size == 0){
            try {
                throw new Exception("Heap is empty");
            } catch (Exception e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

        // Stora la chiave della radice
        int radKey = getEntryKey(heap[0]);

        // Elimina l'ultima entry e inserisci la sua chiave nella radice
        
        heap[0].key = heap[size-1].key;
        heap[size] = null;
        // Decrementa la size
        size--;

        // Fai down-heap bubbling
            int i = 0;
    
            downHeap(i);

        return radKey;
    }

  
    
    public static Heap array2heap(int[] array, HEAP_TYPE type) {

        Heap res = new Heap(type, array.length);

        for(int i = 0; i < array.length; i++){
            
            res.heap[i] = new HeapEntry(array[i], i);
        }
        res.size = array.length;

        int j = res.getParent(res.size() - 1 );
        for(;j >= 0 ; j--){
            // Fai down-heap bubbling
            res.downHeap(j);
            
        }

        
        return res;
    }
    
    public static void heapSort(int[] array) {
        return;
    }
    
    public void updateEntryKey(HeapEntry e, int key) {
        int pos = e.getPosition()-1;
        int temp = heap[pos].key ;

            // System.out.printf("POS: %d",pos);
        heap[pos].key = key;
        
        // Mantiene Heap Order 
        if(compare(pos, getParent(pos))){
            upHeap(pos, getParent(pos));
        }else{
                downHeap(pos);
        }

    }
    
    
    // Aux functions

    public boolean hasLeft(int i){
        return getLeftChild(i) < this.size();
    }
    
    public boolean hasRight(int i){
        return getRightChild(i) < this.size();
    }

    private boolean compare(int i, int j) {
    if(type == HEAP_TYPE.MIN_HEAP){
            return heap[i].getKey() < heap[j].getKey(); 
        }else{
            return heap[i].getKey() > heap[j].getKey(); 
            
        }
    }
    
    private static int getComparisonChild(Heap struct , int index) {

        int rightChild = 2*index+2;
        int leftChild = 2*index+1;

        int r = struct.heap[rightChild].key;
        int l = struct.heap[leftChild].key; 

        if(struct.type == HEAP_TYPE.MIN_HEAP){

            if(l <= r ){
                return leftChild;
            }else{

                return rightChild;
            }
            
            
        }else{
            
            if(l >= r ){
                return leftChild;
            }else{
                
                return rightChild;
            }
        }
    }

    void swap (int i , int j){
        HeapEntry temp = heap[j];

        heap[j] = heap[i];
        heap[j].setPosition(i);
        
        heap[i] = temp;
        heap[i].setPosition(j);
    }
    
    private void increaseHeapCapacity() {
        HeapEntry[] temp = new HeapEntry[capacity*2];
        for (int i = 0; i < capacity; i++) {
            temp[i] = heap[i];
        }
        heap = temp;
        capacity = capacity*2;
    }

    public int getParent(int pos){
        if(pos <= 0){
            return 0;
        } 
        return (pos - 1)/2 ;
    }

    public int getLeftChild (int pos) {
        
        return 2 * pos + 1;
        
    }

    public int getRightChild (int pos) {
        
       return 2 * pos + 2;
      
      
    }

    public HEAP_TYPE getType() {
        return type;
    }

    public int peek() {
        return getEntryKey(heap[0]);
        
    }

    public int getEntryKey(HeapEntry e) {
        return e.getKey();
    }

    public int size() {
        return size;
    }

    public void print() {
        
        
        for(int i = 0; i < this.size;i++){
            System.out.print(" " + getEntryKey(heap[i]));
        }
        System.out.printf("\n");
        
        
        return;
    }
    

}
