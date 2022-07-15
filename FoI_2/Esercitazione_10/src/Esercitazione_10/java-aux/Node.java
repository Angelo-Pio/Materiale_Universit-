public	class Node<V> {

	public static enum Stato{
		UNEXPLORED, EXPLORING, EXPLORED;
	};
	

	private V element;
	public Stato stato;
	private Edge<V> edge = null ;

	int map; // Usato da partition union e find
	
	public Node(V e) {
		element = e;
		stato = Stato.UNEXPLORED;
	}

	public V getElement() { return element; } 
	public Edge<V> getConnectEdge() {
		return edge;
	}

	public void setConnectEdge(Edge<V> edge) {
		this.edge = edge;
	}
	public String toString() {
		return element.toString();
	}
}

