
import java.util.ArrayList;

public class Heap {


    public enum HEAP_TYPE {MAX_HEAP, MIN_HEAP};

    public static class HeapEntry {

        public int key;
       // public int value; key == value
        public int position;
// ultima pos occupata !!
        public HeapEntry(int key ) {
            this.key = key;
        }

        public void setPosition(int position) {
            this.position = position;
        }
        
        
    }

    private HEAP_TYPE type;
    private ArrayList<HeapEntry> heap;
    
    public Heap(HEAP_TYPE type, int capacity) {
    
        this.type = type;
        this.heap = new ArrayList<HeapEntry>(capacity);
    
    }

    public HEAP_TYPE getType() {
        return this.type;
    }

    public int peek() {
        return this.heap.get(0).key;
    }

    public int size() {
        return heap.size();
    }
    

    public int getEntryKey(HeapEntry e) {
        return e.key;
    }


    public int poll() {
        return 0;
    }

    public HeapEntry add(int key) {
        

         HeapEntry e = new HeapEntry(key);
        heap.add(e); // aggiunge alla fine 
        this.upheap(heap.size()-1);
        return e;
    }
    public static Heap array2heap(int[] array, HEAP_TYPE type) {
        
        Heap H = new Heap(type, array.length);
        
        for (int i = 0; i < array.length; i++) {
            
            H.heap.add(new HeapEntry(array[i]));
            H.downHeap();
        }
        
        
        
        
        
        return H;
    }

    public void print() {
        
        int size = this.heap.size();
        
        for (int i = 0; i < size; i++) {
            
            HeapEntry e = this.heap.get(i);
            System.out.printf(" %d ", e.key);
        }
        
        System.out.printf("\n");
        
        
        return;
    }

    public static void heapSort(int[] array) {
        return;
    }

    public void updateEntryKey(HeapEntry e, int key) {
        return;
    }

    
    public void upheap(int i){
    
        while(i > 0){
            int p = this.parent(i);
            
            if(heap.get(i).key > heap.get(p).key ){
                break;
            }
            
            this.swap(i,p);
            
            i = p;
        }
        
    }
    
    private void downHeap() {
        
        
        
        int leftChild = this.leftChild(0);

    }
    
    public int parent(int i){
    
        return (i-1) / 2;
    }
    public int leftChild(int i){
    
        return 2*i+1;
    }
    public int rightChild(int i){
    
        return 2*i - 2 ;
    }
    
    public void swap(int i , int j){
        
        HeapEntry a = this.heap.get(i);
        HeapEntry b = this.heap.get(j);
        
        heap.set(i, b);
        heap.set(j, a);
        
    }
    
    
    
    
}
