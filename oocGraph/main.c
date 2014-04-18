//
//  main.c
//  oocGraph
//
//  Created by Xavier on 14-1-23.
//  Copyright (c) 2014年 Xavier Woo. All rights reserved.
//

#include <stdlib.h>
#include "cGAlg.h"
#include "cGraph.h"


int main(int argc, const char * argv[])
{
    struct Graph *g = NULL;
    g = Graph(g);
    
    Graph_addNode(g, "a");
    Graph_addNode(g, "b");
    Graph_addNode(g, "c");
    Graph_addNode(g, "d");
    Graph_addNode(g, "e");
    
    
        
    Graph_addEdge(g, 0, 1, 1);
    Graph_addEdge(g, 1, 0, 1);
    
    Graph_addEdge(g, 1, 2, 1);
    Graph_addEdge(g, 2, 1, 1);
    
    Graph_addEdge(g, 2, 3, 1);
    Graph_addEdge(g, 3, 2, 1);
    
    Graph_addEdge(g, 3, 4, 1);
    Graph_addEdge(g, 4, 3, 1);
    
    Graph_addEdge(g, 1, 3, 3);
    Graph_addEdge(g, 3, 1, 3);
    
    
    Graph_printGraph(g);
    
    return 0;
}

