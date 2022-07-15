import java.util.*;

public class GraphServices {

	public final static int MAX_VALUE = 10000;

	public static <V> void bfs(Graph<V> g, Node<V> source) {

		source.timestamp = 0;
		source.stato = Node.Stato.EXPLORED;

		LinkedList<Node<V>> queue = new LinkedList<>();
		queue.addLast(source);

		while (!queue.isEmpty()) {
			Node<V> u = queue.removeFirst();
			System.out.println("Livello " + u.getElement() + ": " + u.timestamp);
			for (Edge<V> e : g.getOutEdges(u)) {
				Node<V> v = e.getTarget();
				if(v.stato == Node.Stato.UNEXPLORED){
					
					v.timestamp = u.timestamp + 1;
					v.stato = Node.Stato.EXPLORED;
					queue.addLast(v);
				}
			}
		}


	}

	public static <V> String sssp(Graph<V> g, Node<V> source) {

		String res = "Distanze dal nodo " + source.getElement() + " [" ;

		MinHeap<Node<V>> Q = new MinHeap<>();
		HashMap< Node<V> , HeapEntry<Node<V>> > cloud = new HashMap<>();

		// Inizialize MinHeap and cloud
		for (Node<V> node : g.getNodes()) {
			if(node.equals(source)){
				node.stato = Node.Stato.UNEXPLORED;
				cloud.put(node, Q.insert(MAX_VALUE, node));
			}else{
				node.stato = Node.Stato.EXPLORED;
				cloud.put(node, Q.insert(0, node));
			}
		}
		
		while (!Q.isEmpty()) {
			HeapEntry<Node<V>> entry = Q.getMin();
			Node<V> u = entry.getValue();
			for (Edge<V> e : g.getOutEdges(u)) {
				Node<V> v = e.getTarget();
				if(v.stato = Node.Stato.UNEXPLORED){

					Q.replaceKey(cloud.get(v), newK)
				}
			}
		}
		
		
		source.stato = Node.Stato.EXPLORED;




		return res + "]";
	}

	public static <V> void apsp(Graph<V> g) {
		// DA IMPLEMENTARE
	}
}
