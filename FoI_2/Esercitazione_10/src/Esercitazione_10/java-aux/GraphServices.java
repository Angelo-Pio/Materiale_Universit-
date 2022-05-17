import java.util.*;

public class GraphServices {

	
	public static <V> void bfs(Graph<V> g) {
            
            for (Node<V> node : g.getNodes()) {
                if(node.stato != Node.Stato.EXPLORED){
                    
                    bfsFromNode(node,g);
                    
                }
            }
            
	}

	public static <V> void sssp(Graph<V> g, Node<V> source) {

	}
	
	public static <V> void mst(Graph<V> G) {
		
	}

    private static <V> void bfsFromNode(Node<V> node, Graph<V> g) {

        
        LinkedList<Node<V>> queue = new LinkedList<>();
        
        //Inserisci il primo nodo da cui far partire la bfs nella coda
        queue.addFirst(node);
        
        while (! queue.isEmpty()) {
            
            //Analizza il nodo in testa alla coda
            Node<V> Qnode = queue.removeFirst(); 
            
            Qnode.stato = Node.Stato.EXPLORED;
            
            System.out.println(Qnode.getElement().toString()); // stampa
            
            // Prendi tutti i nodi collegati a qnode e se inesplorati inseriscili a in coda alla coda
            for (Edge<V> outEdge : g.getOutEdges(Qnode)) {
                
                Node<V> v = outEdge.getTarget();
                if(v.stato != Node.Stato.EXPLORED){
                    
                    queue.addLast(v);
                    
                }
            }
            
        }
        
    }
}




