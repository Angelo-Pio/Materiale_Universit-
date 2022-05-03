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

    protected LinkedList<GraphNode<V>> nodesList;
    protected int n_nodes;
    protected int n_edges;
    
    
    
    public Graph () {
        this.nodesList = new LinkedList<>();
    }

    public Graph(int n_nodes, int n_edges) {
        this.nodesList = new LinkedList<>();
        this.n_nodes = n_nodes;
        this.n_edges = n_edges;
    }
    
    

    public List<GraphNode<V>> getNodes() {
        
        if(nodesList.equals(null)){
            return null;
        }
        
        return nodesList;
    }

    public List<GraphNode<V>> getNeighbors(GraphNode<V> n){
        
        if(nodesList.equals(null)){
           return null; 
        }
        
        LinkedList<GraphNode<V>> neighbors = new LinkedList<>();
        
        for (GraphNode<V> node : nodesList) { // Scandisci tutti i nodi del grafo

            if(node.equals(n)){ // Trova n
                
                // Aggiungi tutti i vicini di n alla lista dei vicini da restituire
                for (GraphNode<V> neighbor : node.outEdges) { 
                    
                    neighbors.add(neighbor);
                    
                }
                
            }
        }
        
        return neighbors;
    }

    public GraphNode<V> addNode(V value) {
        
        for (GraphNode<V> graphNode : nodesList) {
            if(graphNode.value == value){
                return null;
            }
        }
        
        GraphNode<V> newNode = new GraphNode<>(value);
        nodesList.add(newNode);
        
        return newNode;
        
    }

    public void addEdge(GraphNode<V> s, GraphNode<V> t) {
        
        for (GraphNode<V> graphNode : nodesList) {
            
            if(graphNode.equals(s)){ // Trova s
                
                addEdge_aux(graphNode, t);
            }
            if(graphNode.equals(t)){
                addEdge_aux(graphNode, s);
            }
        }
    }
    
    private void addEdge_aux(GraphNode<V> graphNode, GraphNode<V> t){
        
        boolean addEdge = true;
        
        if(graphNode.outEdges == null){return;}
        
        // Controlla che non vi sia già t nei vicini di s
                for (GraphNode<V> neighbor : graphNode.outEdges) {
                    if(neighbor.equals(t)){
                        addEdge = false;
                        break;
                    }
                }
                
                // Aggiungi t nei vicini di s 
                if (addEdge) {
                    graphNode.outEdges.add(t);
                }
    
    }

    public V getNodeValue(GraphNode<V> n) {
        
        for (GraphNode<V> graphNode : nodesList) {
            if(graphNode.equals(n)){return graphNode.value;}
        }
        return null;
    }

    public void removeEdge(GraphNode<V> v1, GraphNode<V> v2){
        
        for (GraphNode<V> graphNode : nodesList) {
            
            if(graphNode.equals(v1)){
                
                if(graphNode.outEdges == null){return;}
                graphNode.outEdges.remove(v2);
            
            }
            if(graphNode.equals(v2)){
                if(graphNode.outEdges == null){return;}
                graphNode.outEdges.remove(v1);
            
            }
            
        }
        
    }

    public void removeNode(GraphNode<V> v){

        // Elimina tutti gli archi che connettono il nodo
        
        for (GraphNode<V> graphNode : nodesList) {
            
            if(graphNode.equals(v)){
            
                if(graphNode.outEdges == null){return;}
                else{
                
                    
                    for (Iterator<GraphNode<V>> iterator = nodesList.iterator(); iterator.hasNext();) {
                        GraphNode<V> next = iterator.next();
                        removeEdge(v, next);
                    }
                }
                    
            
            }
        }
        
        
        
        //Elimina alla fine il nodo dal grafo
        
        nodesList.remove(v);
    }

    public static <V> Graph<V> readFF(File input){
        
        Graph<V> ret = new Graph<>();
        
        try {
            BufferedReader br = new BufferedReader(new FileReader(input));
            
            String firstLine = br.readLine();
            StringTokenizer tok = new StringTokenizer(firstLine," ");
            int v = Integer.parseInt(tok.nextToken());
            int e = Integer.parseInt(tok.nextToken());
            
            ret = new Graph<V>(v, e);
            
            for (int i = 0; i < e; i++) {
                String line = br.readLine();
                
                tok = new StringTokenizer(line);
                while(tok.hasMoreTokens()){

                    GraphNode<V> v1 = ret.addNode((V) tok.nextToken());
                    GraphNode<V> v2 = ret.addNode((V) tok.nextToken());
                    ret.addEdge(v1, v2);
                }
            }
            br.close();
            
            
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        
        
        return ret;
        
    }

     public String printAdj() {
    	StringBuffer toRet = new StringBuffer();
        for(GraphNode<V> v : this.nodesList) {
      	  toRet.append(v.value + ": ");
      	  for(GraphNode<V> e: v.outEdges) {
      		  toRet.append(e.value + " ");
      	  }
      	  toRet.append("\n");
        }
        return toRet.toString();
    }
    
    @Override
    public String toString(){
    	StringBuffer toRet = new StringBuffer();
    	for(GraphNode<V> node : this.nodesList) {
    		if(node.state == GraphNode.Status.UNEXPLORED)
    			DFSprintEdges(node, toRet);
    	}
    	return toRet.toString();
    }
    
    private void DFSprintEdges(GraphNode<V> node, StringBuffer str) {
    	if(node.state != GraphNode.Status.UNEXPLORED)
    		return;
    	node.state = GraphNode.Status.EXPLORING;
    	for(GraphNode<V> e : node.outEdges) {
    		if(e.state == GraphNode.Status.UNEXPLORED)
    			str.append(node.value + " " + e.value + "\n");
    	}
    	for(GraphNode<V> e : node.outEdges) {
    		if(e.state == GraphNode.Status.UNEXPLORED)
    			DFSprintEdges(e, str);
    	}
    	node.state = GraphNode.Status.EXPLORED;
	}

    public int nConComp(){
        
            int count = 0;
            LinkedList<GraphNode<V>> compConn = new LinkedList<>();
            
            for (GraphNode<V> graphNode : nodesList) {
                if(graphNode.state == graphNode.state.UNEXPLORED){
                    count++;
                    DFS(graphNode);
                }
            }
                
        
            return count;
    }

    private void DFS(GraphNode<V> node) {
    	if(node.state != GraphNode.Status.UNEXPLORED)
    		return;
    	node.state = GraphNode.Status.EXPLORING;
    	for(GraphNode<V> e : node.outEdges) {
    		if(e.state == GraphNode.Status.UNEXPLORED)
    			DFS(e);
    	}
    	node.state = GraphNode.Status.EXPLORED;
	}

    public List<Graph<V>> getConComp(){
            LinkedList<Graph<V>> ret = new LinkedList<>();
            
            for (GraphNode<V> graphNode : nodesList) {
                
                if(graphNode.state == graphNode.state.UNEXPLORED){
                    LinkedList<GraphNode<V>> nodes = new LinkedList<>();
                    DFSfillCC(graphNode, nodes);
                    
                    Graph<V> subGraph = new Graph<>();
                    
                    for (GraphNode<V> node : nodes) {
                        subGraph.nodesList.add(node);
                    }
                    ret.add(subGraph);
                }
                
            }
            
            
            return ret;
            
            
    }

    private void DFSfillCC(GraphNode<V> node, LinkedList<GraphNode<V>> list) {
    	if(node.state != GraphNode.Status.UNEXPLORED)
    		return;
    	node.state = GraphNode.Status.EXPLORING;
    	list.add(node);
    	for(GraphNode<V> n : node.outEdges) {
    		if(n.state == GraphNode.Status.UNEXPLORED)
    			DFSfillCC(n, list);
    	}
    	node.state = GraphNode.Status.EXPLORED;
	}

   

    
    // GraphNode Class
    
    public static class GraphNode<V> implements Cloneable{

    public enum Status {UNEXPLORED, EXPLORED, EXPLORING}

    protected V value;
    protected LinkedList<GraphNode<V>> outEdges = new LinkedList<>();

        public GraphNode(V value) {
            this.value = value;
        }

    
    
    
    // keep track status
    protected Status state = Status.UNEXPLORED;

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
