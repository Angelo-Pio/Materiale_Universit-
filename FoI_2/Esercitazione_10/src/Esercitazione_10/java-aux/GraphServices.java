import java.security.KeyStore.Entry;
import java.util.*;
import java.util.concurrent.ConcurrentLinkedQueue;

public class GraphServices {

	
	public static <V> void bfs(Graph<V> g) {
            
        for ( Node<V> v : g.getNodes()) {
            if(v.stato == Node.Stato.UNEXPLORED){

                bfsFromNode(v, g);
            }
        }
            
	}

	public static <V> void sssp(Graph<V> g, Node<V> source) {

        MinHeap<Node<V>> pqueue = new MinHeap<Node<V>>();

		HashMap<Node<V>, HeapEntry<Node<V>>> dist = new HashMap<Node<V>, HeapEntry<Node<V>>>();


		final int INFINITY = 100000; // = "Infinito"
		// (NB.: deve essere maggiore della somma di tutti i pesi del grafo, altrimenti e' scorretto)

		// Inizializzazione

		for(Node<V> u : g.getNodes()) {
			HeapEntry<Node<V>> hu = pqueue.insert(u == source ? 0 : INFINITY, u);
			dist.put(u, hu);
		}

		// Ciclo principale

		while (!pqueue.isEmpty()) {
			HeapEntry<Node<V>> hu = pqueue.removeMin();
			Node<V> u = hu.getValue();

			for(Edge<V> e : g.getOutEdges(u)) {

				Node<V> v = e.getTarget();
				if (dist.get(u).getKey() + e.getWeight() < dist.get(v).getKey()) {
					pqueue.replaceKey(dist.get(v), dist.get(u).getKey() + e.getWeight());
				}

			}

		}

		for(Node<V> u : g.getNodes()) {
			System.out.println(u + " " + dist.get(u).getKey());
		}

        
    }
	
	public static <V> void mst(Graph<V> G) {
		
	}

    private static <V> void bfsFromNode(Node<V> node, Graph<V> g) {

        ArrayDeque<Node<V>> Q = new ArrayDeque<>();
        
        node.stato = Node.Stato.EXPLORED;
        Q.add(node);
        
        while(! Q.isEmpty()){
                Node<V> u = Q.remove();
                System.out.println(u.getElement());
                for (Edge<V> e : g.getOutEdges(u)) {
                    Node<V> v = e.getTarget();
                    if(v.stato == Node.Stato.UNEXPLORED){
                        v.stato = Node.Stato.EXPLORED;
                        Q.add(v);
                    }
                }
            
           
        }
        
        
    }
}




