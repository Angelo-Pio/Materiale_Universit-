public class MaxGap {

    public static int maxGap(int[] array, int start, int end) {
      	
//        int midL = (end-1)/2; 
//        int midR = ((end-1) + start) / 2 + start ;
        int size = end - start;
        int mid = start + (size / 2);

        System.out.printf("Start: %d End: %d \n", start,end);
        
        if(end - start == 2 ){ // Corretto
            return array[start + 1] - array[start];
        }
        
        int leftGap = maxGap(array,start,mid +1);  // Fin qui left Gap funziona
        
        int rightGap = maxGap(array,mid,end);
        
        return leftGap > rightGap ? leftGap : rightGap;
        
    }  
    
    
        
                
        
   
}
