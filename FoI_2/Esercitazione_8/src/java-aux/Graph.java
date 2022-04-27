import java.util.LinkedList;
import java.util.List;
import java.io.File;

public class Graph<V> {

    protected LinkedList<GraphNode<V>> nodesList;
    
    public Graph () {
        this.nodesList = new LinkedList<>();
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
                    
                for (GraphNode<V> outEdge : graphNode.outEdges) {


                    removeEdge(v, outEdge);
                }
            
            }
        }
        
        
        
        //Elimina alla fine il nodo dal grafo
        
        nodesList.remove(v);
    }

    public static <V> Graph<V> readFF(File input){
      return null;
    }

    public String printAdj() {
        
        String adjString = "";
        
        for (GraphNode<V> graphNode : nodesList) {
            if (graphNode.outEdges == null) {
                continue;
            }
            for (GraphNode<V> outEdge : graphNode.outEdges) {
                adjString += outEdge.toString() + "\n";
            }
        }
        
        return adjString;
    }

    @Override
    public String toString(){
        
        String ret = "(";
        
        for (GraphNode<V> graphNode : nodesList) {
            ret += graphNode.toString()+"\t";
        }
        
        ret += ")";

        return ret;
        
    }

    public int nConComp(){
      return 0;
    }

    public List<Graph<V>> getConComp(){
      return null;
    }

    
    // GraphNode Class
    
    public static class GraphNode<V> implements Cloneable{

    public enum Status {UNEXPLORED, EXPLORED, EXPLORING}

    protected V value;
    protected LinkedList<GraphNode<V>> outEdges;

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
