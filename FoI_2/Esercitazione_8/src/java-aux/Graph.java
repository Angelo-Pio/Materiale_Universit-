import java.io.BufferedReader;
import java.util.LinkedList;
import java.util.List;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.StringTokenizer;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Graph<V> {

    LinkedList<GraphNode<V>> nodes;
    public int numEdges;
    public int numVertices;

    public Graph() {

        nodes = new LinkedList<GraphNode<V>>();
        numEdges = 0;
        numVertices = 0;
    }

    public List<GraphNode<V>> getNodes() {
        return nodes;
    }

    // Cosa sono i vicini?
    public List<GraphNode<V>> getNeighbors(GraphNode<V> n) {

        List<GraphNode<V>> res = new LinkedList<GraphNode<V>>();

        for (GraphNode<V> outNode : n.outEdges) {
            try {
                res.add((GraphNode<V>) outNode.clone());
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
            }
        }

        return res;
    }

    public GraphNode<V> addNode(V value) {
        GraphNode<V> node = new GraphNode<V>(value);
        
        for (GraphNode<V> graphNode : nodes) {
            if (graphNode.value.equals(value)) {
                return graphNode;
            }
        }
        
        nodes.add(node);
        numVertices++;
        return node;
    }

    public void addEdge(GraphNode<V> s, GraphNode<V> t) {

        s.outEdges.add(t);
        t.outEdges.add(s);

        numEdges++;
        return;
    }

    public V getNodeValue(GraphNode<V> n) {
        for (GraphNode<V> node : nodes) {
            if (node == n) {
                return node.value;
            }
        }
        return null;
    }

    public void removeEdge(GraphNode<V> v1, GraphNode<V> v2){
    	removeEdgeAux(v1,v2);
    	removeEdgeAux(v2,v1);
		this.numEdges--;
    }
    
    private void removeEdgeAux(GraphNode<V> v1, GraphNode<V> v2) {
    	Iterator<GraphNode<V>> it = this.nodes.iterator();
    	while(it.hasNext()) {
    		GraphNode<V> n1 = it.next();
    		Iterator<GraphNode<V>> it2 = n1.outEdges.iterator();
    		if(n1.equals(v1)) {
	    		while(it2.hasNext()) {
	    			GraphNode<V> n2 = it2.next();
	    			if(n2.equals(v2)) { 
	    				it2.remove();
	    			}
	    		}
    		}
    	}
    }

    public void removeNode(GraphNode<V> v){
    	if(this.nodes.contains(v)) {
	    	for(GraphNode<V> e : v.outEdges) {
	    		this.removeEdgeAux(e, v);
	    		this.numEdges--;
	    	}
    	}
    	this.nodes.remove(v);
    }

    public static <V> Graph<V> readFF(File input) throws IOException {

        Graph<V> g = new Graph<>();
        
        try {
            BufferedReader br = new BufferedReader(new FileReader(input));

            String firstLine = br.readLine();
            StringTokenizer tk = new StringTokenizer(firstLine," ");

            g.numEdges = Integer.parseInt(tk.nextToken());
            g.numVertices = Integer.parseInt(tk.nextToken());

            for (int i = 0; i < g.numEdges; i++) {
                StringTokenizer tok = new StringTokenizer(br.readLine()," ");
                
                V val = (V)tok.nextToken();
                g.addNode(val);
                GraphNode<V> v1 = new GraphNode<V>(val);
                
                val = (V)tok.nextToken();
                g.addNode(val);
                GraphNode<V> v2 = new GraphNode<V>(val);
                
                g.addEdge(v1, v2);
            }

        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        return g;
    }

    public String printAdj() {

        return this.toString();
    }

    @Override
    public String toString() {

        StringBuffer str = new StringBuffer();

        str.append(this.numEdges+" " + this.numVertices+"\n\n");
        
        printDFS(str);

        resetStatus(nodes.getFirst());

        return str.toString();

    }

    private void printDFS(StringBuffer str) {
        for (GraphNode<V> node : nodes) {
            printDFS_aux(str, node);
        }
    }

    private void resetStatus(GraphNode<V> node) {
        node.state = GraphNode.Status.UNEXPLORED;

        for (GraphNode<V> n : node.outEdges) {
            if(n.state == GraphNode.Status.EXPLORED){
                resetStatus(n);
            }
        }
    }

    

    public void printDFS_aux(StringBuffer buff, GraphNode<V> node){
        
        node.state = GraphNode.Status.EXPLORED;

        for (GraphNode<V> n : node.outEdges) {
            if(n.state == GraphNode.Status.UNEXPLORED){
                buff.append((String)node.value + " " + n.value + "\n");
                printDFS_aux(buff, n);
            }
        }

    }


    public int nConComp() {
        return 0;
    }

    public List<Graph<V>> getConComp() {
        return null;
    }

    public static class GraphNode<V> implements Cloneable {

        public enum Status {
            UNEXPLORED, EXPLORED, EXPLORING
        }

        protected V value;
        protected LinkedList<GraphNode<V>> outEdges;
        // keep track status
        protected Status state;

        public GraphNode(){outEdges = new LinkedList<>();}

        public GraphNode(V value) {
            this();
            this.value = value;
            this.state = Status.UNEXPLORED;
        }

        public GraphNode(V value, Status state) {
            this(value);
            this.state = state;
        }

        @Override
        public String toString() {
            return "GraphNode [value=" + value + ", state=" + state + "]";
        }

        @Override
        protected Object clone() throws CloneNotSupportedException {
            return super.clone();
        }

    }

}
