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
                String str = br.readLine();
                if(str == null) break;
                StringTokenizer tok = new StringTokenizer(str," ");
                
                V val = (V)tok.nextToken();
                g.addNode(val);
                GraphNode<V> v1 = g.nodes.getLast();
                
                val = (V)tok.nextToken();
                g.addNode(val);
                GraphNode<V> v2 = g.nodes.getLast();
                
                g.addEdge(v1, v2);
            }

        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        return g;
    }

    public String printAdj() {
        StringBuffer str = new StringBuffer();
        for (GraphNode<V> graphNode : nodes) {
            str.append(graphNode.value+"-");
        }
        str.append("\n"+this.toString());
        return str.toString();
    }

    @Override
    public String toString() {

        StringBuffer str = new StringBuffer();

        str.append(this.numEdges+" " + this.numVertices+"\n\n");
        
        resetStatus();
        printDFS(str);
        resetStatus();


        return str.toString();

    }

    private void printDFS(StringBuffer str) {
        for (GraphNode<V> node : nodes) {
            printDFS_aux(str, node);
        }
    }

    private void resetStatus(){
        for (GraphNode<V> node : nodes) {
            if(node.state == GraphNode.Status.EXPLORED){
                resetStatus_aux(node);
            }
        }
    }

    private void resetStatus_aux(GraphNode<V> node) {
        node.state = GraphNode.Status.UNEXPLORED;

        for (GraphNode<V> n : node.outEdges) {
            if(n.state == GraphNode.Status.EXPLORED){
                resetStatus_aux(n);
            }
        }
    }

    

    public void printDFS_aux(StringBuffer buff, GraphNode<V> node){
        
        if(node.state == GraphNode.Status.EXPLORING){
            for (GraphNode<V> m : node.outEdges) {
                if(m.state == GraphNode.Status.EXPLORED){
                    buff.append((String)node.value + " " + m.value + "\n");
                }
            }
        }
        node.state = GraphNode.Status.EXPLORED;

        for (GraphNode<V> n : node.outEdges) {
            if(n.state == GraphNode.Status.UNEXPLORED){
                buff.append((String)node.value + " " + n.value + "\n");
                n.state = GraphNode.Status.EXPLORING;
                printDFS_aux(buff, n);
            }
        }

    }


    public int nConComp() {
        int count = 0;
        resetStatus();

        for (GraphNode<V> node : nodes) {
            if(node.state == GraphNode.Status.UNEXPLORED){
                DFS(node);
                count++;
            }
        }

        return count;
    }

    private void DFS(Graph.GraphNode<V> node) {
        node.state = GraphNode.Status.EXPLORED;
        for (GraphNode<V> n : node.outEdges) {
            if(n.state == GraphNode.Status.UNEXPLORED){
                DFS(n);
            }
        }
    }

    public List<Graph<V>> getConComp() {
        List<Graph<V>> list = new LinkedList<Graph<V>>();
        Graph<V> g = new Graph<>();
        for (GraphNode<V> n : nodes) {

            if(n.state == GraphNode.Status.UNEXPLORED){
                DFS_Conn(n,g);
                list.add(g);
                g = new Graph<>();
            }
            
        }
        return list;
    }

   

    private void DFS_Conn(Graph.GraphNode<V> node, Graph<V> g) {

        node.state = GraphNode.Status.EXPLORED;
        for (GraphNode<V> n : node.outEdges) {
            if(n.state == GraphNode.Status.UNEXPLORED){
                g.nodes.add((GraphNode<V>)n.clone());
                g.numVertices++;
                g.numEdges++;
                
                DFS_Conn(n,g);

            }
        }

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
