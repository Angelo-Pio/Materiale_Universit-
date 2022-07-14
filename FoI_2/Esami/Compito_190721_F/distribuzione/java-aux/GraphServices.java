import java.util.*;

public class GraphServices {

	public static <V> void bfs(Graph<V> g, Graph.GraphNode<V> source) {

		g.resetStatus();
		LinkedList<Graph.GraphNode<V>> queue = new LinkedList<>();
		source.state = Graph.GraphNode.Status.EXPLORING;

		queue.addLast(source);

		while (!queue.isEmpty()) {
			Graph.GraphNode<V> u = queue.removeFirst();
			System.out.println("Livello " + u.value + ": " + u.timestamp);
			for (Graph.GraphNode<V> v : u.outEdges) {
				if (v.state == Graph.GraphNode.Status.UNEXPLORED) {
					v.timestamp = u.timestamp + 1;
					v.state = Graph.GraphNode.Status.EXPLORING;
					queue.addLast(v);
				}
			}
			u.state = Graph.GraphNode.Status.EXPLORED;

		}
		g.resetStatus();

	}

}
