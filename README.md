oocGraph
========

A directed simple graph api written in c with an object-oriented programming style


The file "oocGraph.h" should be included.

To create a graph:

    struct Graph *g = NULL;
    g = Graph(g);


To destroy the graph:

    del_Graph(g);


To add a node to the graph:

    g->addNode(g, "The name of the node"); 
    //The id of the new added node will be returned. The id can be found in the array g->nodeSet[struct Node].


To add an edge to the graph
    
    g->addEdge(g, id_of_source_node, id_of_sink_node, cost_of_the_edge);
    //A pointer pointing to the new added edge will be returned.


To remove an edge to the graph

    g->removeEdge(g, id_of_source_node, id_of_sink_node);


To get the edge cost

    cost = g->edgeCost(g, id_of_source_node, id_of_sink_node);
