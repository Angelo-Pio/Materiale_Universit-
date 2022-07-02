import java.util.LinkedList;
import java.util.List;


public class GraphServices<V> {


    public enum EdgeType {
        TREE, BACK, FORWARD, CROSS
    };

    public static <V> void topologicalSort(Graph<V> g) {

        StringBuffer str = new StringBuffer();

        for (Graph.GraphNode<V> node : g.getNodes()) {
            if(node.inEdges.size() == 0){
                topDFS(node,str);
                if(str.toString() == "Not a DAG"){
                    break;
                }
            }
        }

        str.append(",");
        System.out.println(str.toString());
    }

    private static <V> void topDFS(Graph.GraphNode<V> node, StringBuffer str) {
        
        node.state = Graph.GraphNode.Status.EXPLORED;

        for (Graph.GraphNode<V> n : node.outEdges) {
            if(n.state == Graph.GraphNode.Status.UNEXPLORED){
                topDFS(n, str);
            }
            else{
                str.replace(0, str.capacity(), "Not a DAG");
                return;
            }
        }
       
        
    }

    public static <V> void strongConnectedComponents(Graph<V> g) {

        // Idea: Creare due liste di componenti connesse
        // Una a partire da G ed un'altra a partire da G trasposto
        // se vi sono due componenti connesse uguali allora si ha una componente fortemente connessa

    }

    
    
    public static <V> void sweep(Graph<V> g) {

        List<Graph.GraphNode<V>> nodes = g.getNodes();
        for(Graph.GraphNode<V> n : nodes){
            if(n.state == Graph.GraphNode.Status.UNEXPLORED){

                sweep_aux(n);
            }
        }
       

    }

    public static <V> void printEdgeType(Graph.GraphNode<V> node, Graph.GraphNode<V> n , String type){
        System.out.println(node.value + "->" + n.value + " : {"+type+"}");
    }

    public static <V> void sweep_aux(Graph.GraphNode<V> node){
    
        node.state = Graph.GraphNode.Status.EXPLORING;
        node.timestamp++;
        
        for (Graph.GraphNode<V> n : node.outEdges) {
            if(n.state == Graph.GraphNode.Status.UNEXPLORED){
                
                printEdgeType(node, n, "TREE");
                
                sweep_aux(n);
                
                
                
            }else if(n.state == Graph.GraphNode.Status.EXPLORING){
                
                printEdgeType(node, n, "BACK");
            }
            else{
                if(n.timestamp > node.timestamp){
                    printEdgeType(node, n, "FORWARD");
                }else{
                    printEdgeType(node, n, "CROSS");
                    
                }
                return;
            }
        }
        
        node.state = Graph.GraphNode.Status.EXPLORED;

    }

    // Sweep:
    // Visita il grafo tramite dfs
    // Ogni volta che viene visitato incrementa il suo timestamp
    // Un nodo passa per tre stadi UNEXPLORED -> EXPLORING -> EXPLORED





    

}
