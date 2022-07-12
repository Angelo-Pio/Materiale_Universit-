public class GraphServices {

	/**
 	* Dato un grafo g, la funziona ritorna il numero delle sue componenti connesse.
	*/
	public static int connComp(Graph g){

		int answ = 0;

		for (GraphNode node : g.getNodes()) {

			if(node.tag == Graph.UNEXPLORED){
				connComp(node);
				answ++;
			}
			
		}

		return answ;
	}

	private static void connComp(GraphNode node) {
		node.setNodeTag(Graph.EXCLUDED);

		for (GraphEdge e : node.incidentEdges) {
			GraphNode v = e.getEdgeOpposite(node);

			if(v.getNodeTag() == Graph.UNEXPLORED){
				connComp(v);
			}	

		}
	}

	/**
	 * Dato un grafo g, la funzione modifica il grafo contraendone tutti i vertici di grado 2.
	 */ 
	public static void contract(Graph g){
		for (GraphNode node : g.getNodes()) {
			if(getDegree(node) == 2){
				GraphEdge e1 =  node.incidentEdges.get(0);
				GraphEdge e2 =  node.incidentEdges.get(1);

				GraphNode v = e1.getEdgeOpposite(node);
				GraphNode w = e2.getEdgeOpposite(node);

				// Controlla che non esiste e3
				boolean canContract = true;
				for (GraphEdge e3 : v.incidentEdges) {
					if(e3.getEdgeOpposite(v).equals(w)){
						canContract = false;
					}
				}

				if(canContract){

					g.removeNode(node);
					g.addEdge(v, w);
					
				}


			}
		}
	}

	public static int getDegree(GraphNode n){
		return n.incidentEdges.size();
	}

	/**
	 * Dato un grafo g, ritorna il numero di sottografi completi di 3 nodi contenuti in g
	 */
	public static int countK3(Graph g){

		int answ = 0;
		for (GraphNode node : g.getNodes()) {
			if(getDegree(node) == 2){
				GraphEdge e1 =  node.incidentEdges.get(0);
				GraphEdge e2 =  node.incidentEdges.get(1);

				GraphNode v = e1.getEdgeOpposite(node);
				GraphNode w = e2.getEdgeOpposite(node);
				

				// Controlla che non esiste e3
				for (GraphEdge e3 : v.incidentEdges) {
					if(e3.getEdgeOpposite(v).equals(w) ){
						answ++;
						break;
					}
				}

			}
		}
		return answ;
	}
}