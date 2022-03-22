import java.util.*;

public class Sort {

    /* Disponibile in libreria java */
    public void quickSortDefault(int[] array) {
        Arrays.sort(array);
    }

    public void mergeSort(int[] array) {
        System.out.println("mergeSort non è ancora implementato");
        return;
    }

    public void heapSort(int[] array) {
        
        Heap H = new Heap(array.length);
        
        for (int i = 0; i < array.length; i++) {
            H.insert(array[i]);
        }
        
        for (int j = 0; j < H.size(); j++) {
           array[j] = H.removeMin();
        }
    }
 
    public void insertionSort(int[] array) {
        
        int n = array.length;
        for (int i = 1; i < n ; i++) {
            int cur = array[i]; //  Prendi l' elemento corrente
            int j = i;          // prendi il suo indice
            // Trova l' indice in cui posizionare cur
            while (j > 0 && array[j-1] > cur) {   // Finchè non J è 0 e l'elemento che lo precede è più grande...            
                array[j] = array[j-1];
                j--;
            }
            array[j] =cur;
        }
        


    }

    public void selectionSort(int[] array) {
        
        
        for (int i = 0; i < array.length-1; i++) {
            
            int min = i;
            
            for (int j = i+1; j < array.length; j++) {
                
                if(array[j] < array[i]){
                    min = j;
                }
                
            }

            if(min != i){
                int temp = array[i];
                array[i] = array[min];
                array[min] = temp;
            }
            
        }
          


    }

    public void quickSort(int[] array) {
        System.out.println("quickSort non è ancora implementato");
        return;
    }

    public void radixSort(int[] array) {
        System.out.println("radixSort non è ancora implementato");
        return;
    }

    public void bucketSort(int[] array) {
        System.out.println("bucketSort non è ancora implementato");
        return;
    }
    
    
    // Metodi Aux per heapSort
    
    protected class Heap{
        
        private ArrayList<Integer> heap;

        public Heap() {
            heap = new ArrayList<>();
        }
        
        public Heap(int capacity) {
            heap = new ArrayList<>(capacity);
        }
        
        public int size(){ return heap.size();}
        
        protected void insert(int val){
            heap.add(val);
            this.upHeap(heap.size()-1);
        }
        
        protected void upHeap(int i){
            
            while(i > 0){
                
                if(heap.get(i) > heap.get(parent(i)) ){
                    break;
                }
                swap(i, parent(i));
                i--;
            }
            
        }
        
        protected int removeMin(){
            
            int res = heap.get(0);
            
            this.swap(0, heap.size()-1);
            heap.remove(heap.size()-1);
            
            this.downHeap(0);
            
            return res;
            
        }
        
        protected void downHeap(int i){
            
            while(leftChild(i) < heap.size()){
                
                
                
                int c = leftChild(i) ;
                int r  =rightChild(i);
                
                if(r < heap.size()-1){
                    
                    if(heap.get(c) > heap.get(r)){
                        c  = r;
                    }
                }
                
                if( heap.get(i) < heap.get(c)){break;}
                
                swap(i,c);
                
                i=c;
            }
            
        }
        
        protected void swap(int i , int j){
            int tem = heap.get(i);
            heap.set(i, heap.get(j));
            heap.set(j,tem);
        }
        
        
        protected int parent(int i){ return (i-1) / 2;}
        protected int leftChild(int i){ return (i*2 +1);}
        protected int rightChild(int i){ return (i*2 +2);}

        public void to_String() {
            for (int i = 0; i < heap.size(); i++) {
                System.out.printf("%d ", heap.get(i));              
            }
        }
        
        
            
    }
    
    
}
