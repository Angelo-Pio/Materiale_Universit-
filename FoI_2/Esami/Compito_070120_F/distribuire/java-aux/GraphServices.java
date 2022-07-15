import java.util.*;

public class GraphServices {

	/**
	 *
	 */
	private static final int SOURCE_VALUE = 0;
	private static final int MAX_VALUE = 10000;
	private static int rel;

	public static <V> void bfs(Graph<V> g, Node<V> source) {
		LinkedList<Node<V>> Q = new LinkedList<>();
		source.stato = Node.Stato.EXPLORED;
		source.timestamp = 0;
		Q.addLast(source);
		while (!Q.isEmpty()) {
			Node<V> u = Q.removeFirst();
			System.out.println("Livello " + u.getElement() + ": " + u.timestamp);
			for (Edge<V> e : g.getOutEdges(u)) {
				Node<V> v = e.getTarget();
				if (v.stato == Node.Stato.UNEXPLORED) {
					v.stato = Node.Stato.EXPLORED;
					v.timestamp = u.timestamp + 1;
					Q.addLast(v);
				}
			}
		}
	}

	public static <V> String sssp(Graph<V> g, Node<V> source) {
		String r = "Distanze dal nodo " + source.getElement() + " [";
		StringBuilder res = new StringBuilder(r);

		HashMap<Node<V>, HeapEntry<Node<V>>> cloud = new HashMap<>();
		MinHeap<Node<V>> Q = new MinHeap<>();

		for (Node<V> n : g.getNodes()) {

			if (n.equals(source)) {
				n.timestamp = SOURCE_VALUE;
				cloud.put(n, Q.insert(SOURCE_VALUE, n));
			} else {

				n.timestamp = MAX_VALUE;
				cloud.put(n, Q.insert(MAX_VALUE, n));
			}
		}

		while (!Q.isEmpty()) {
			HeapEntry<Node<V>> entry = Q.removeMin();
			Node<V> u = entry.getValue();

			res.append(u.getElement() + ":" + u.timestamp + ", ");

			for (Edge<V> e : g.getOutEdges(u)) {

				Node<V> v = e.getTarget();

				int rel = u.timestamp + e.getWeight();
				if (rel < v.timestamp) {

					v.timestamp = rel;
					v.stato = Node.Stato.EXPLORING;
					Q.replaceKey(cloud.get(v), rel);
				}

			}
		}
		res.replace(res.length()-2, res.length(), "]");
		return res.toString();
	}

	public static <V> void apsp(Graph<V> g) {

		for (Node<V> n : g.getNodes()) {
			System.out.println(sssp(g, n));
		}
	}
}
