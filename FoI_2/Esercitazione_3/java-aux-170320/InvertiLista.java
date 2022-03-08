
import java.util.*;

public class InvertiLista {

	public static void invertiLista(LinkedList<Integer> list) {
         
            if(list.size() > 1){
                
                Integer head = list.pop();
                invertiLista(list);
                list.addLast(head);
            
            }
            
            
        }
}
