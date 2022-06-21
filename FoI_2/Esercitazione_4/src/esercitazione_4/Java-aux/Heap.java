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
        
        while(j != -1 && !compare(i,j)){
            
            swap(i, j);

            i = j;
            j = getParent(i);
        }

        // incrementa la size
        size++;
        return e;
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
            int c;
            int index = 0;
            // Scegli il figlio con cui fare la comparazione
            do{
                if(heap[getRightChild(index)] == null) {
                    c = getLeftChild(index);
                }else{
                    c = getComparisonChild(index);
                }

                swap(c,index);

                index = c;

            }while(index < size && compare(c, index));

        return radKey;
    }
    
    public static Heap array2heap(int[] array, HEAP_TYPE type) {
        return null;
    }
    
    public static void heapSort(int[] array) {
        return;
    }
    
    public void updateEntryKey(HeapEntry e, int key) {
        return;
    }
    
    
    // Aux functions
    private boolean compare(int i, int j) {
    if(type == HEAP_TYPE.MIN_HEAP){
        return heap[i].getKey() >= heap[j].getKey(); 
        }else{
            return heap[i].getKey() <= heap[j].getKey(); 
            
        }
    }
    
    private int getComparisonChild(int index) {

        int r = heap[getRightChild(index)].getKey();
        int l = heap[getLeftChild(index)].getKey(); 

        if(type == HEAP_TYPE.MIN_HEAP){

            if(l <= r ){
                return getLeftChild(index);
            }else{

                return getRightChild(index);
            }
            
            
        }else{
            
            if(l >= r ){
                return getLeftChild(index);
            }else{
                
                return getRightChild(index);
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

    int getParent(int pos){
        if(pos <= 0){
            return 0;
        } 
        return (pos - 1)/2 ;
    }

    int getLeftChild (int pos) throws ArrayIndexOutOfBoundsException{
        
        int lpos = 2 * pos + 1;
        if(lpos > capacity-1){
            throw new ArrayIndexOutOfBoundsException();
        }else{

            return lpos ;
        }
    }

    int getRightChild (int pos) throws ArrayIndexOutOfBoundsException{
        
        int rpos = 2 * pos + 2;
        if(rpos > capacity-1){
            throw new ArrayIndexOutOfBoundsException();
        }else{

            return rpos ;
        }
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
