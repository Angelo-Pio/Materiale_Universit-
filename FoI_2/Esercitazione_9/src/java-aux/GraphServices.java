
public class GraphServices<V> {

    public enum EdgeType {
        TREE, BACK, FORWARD, CROSS
    };

    public static <V> void topologicalSort(Graph<V> g) {

    }

    public static <V> void strongConnectedComponents(Graph<V> g) {

    }

    
    // Nel codice c'è un piccolo errore: non si tiene conto di quando un nodo è stato esplorato
    // bisogna lavorare con il timestamp del nodo per classificare correttamente un arco cross o forward
    
    public static <V> void sweep(Graph<V> g) {

        g.resetStatus();

        for (Graph.GraphNode<V> node : g.getNodes()) {
            if (node.state != Graph.GraphNode.Status.EXPLORED) {
                DFS_classification(node);
            }
        }

    }

    private static <V> void DFS_classification(Graph.GraphNode<V> node) {

        for (Graph.GraphNode<V> outEdge : node.outEdges) {
            EdgeType type = EdgeType.TREE;

            switch (outEdge.state) {

                case EXPLORING:
                    type = EdgeType.BACK;
                    break;
                case EXPLORED:
                    if (node.state != Graph.GraphNode.Status.EXPLORED) { 
                        type = EdgeType.CROSS;
                    } else {
                        type = EdgeType.FORWARD;
                    }
                    break;
            }

            printEdgeType(node, outEdge, type);

        }

        if (node.state != Graph.GraphNode.Status.UNEXPLORED) {
            return;
        }

        node.state = Graph.GraphNode.Status.EXPLORING;

        for (Graph.GraphNode<V> outEdge : node.outEdges) {
            if (outEdge.state == Graph.GraphNode.Status.UNEXPLORED) {
                DFS_classification(outEdge);
            }
        }

        node.state = Graph.GraphNode.Status.EXPLORED;

    }

    private static <V> void printEdgeType(Graph.GraphNode<V> node, Graph.GraphNode<V> outEdge, EdgeType type) {
        String type_s = "";

        switch (type) {
            case TREE:
                type_s = "TREE";
                break;
            case FORWARD:
                type_s = "FORWARD";
                break;
            case BACK:
                type_s = "BACK";
                break;
            case CROSS:
                type_s = "CROSS";
                break;
        }

        String buffer = node.value + " -> " + outEdge.value + " : " + '{' + type_s + '}';
        System.out.println(buffer);
    }

}
