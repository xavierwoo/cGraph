//
//  main.c
//  oocGraph
//
//  Created by Xavier on 14-1-23.
//  Copyright (c) 2014年 Xavier Woo. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "oocGraph.h"
int main(int argc, const char * argv[])
{
    struct Graph *g = NULL;
    
    g = Graph(g);
    g->addNode(g, "a");
    g->addNode(g, "b");
    g->addNode(g, "c");
    g->addNode(g, "d");
    g->addNode(g, "e");
    
    
        
    g->addEdge(g, 0, 1, 1);
    g->addEdge(g, 1, 2, 1);
    g->addEdge(g, 2, 3, 1);
    g->addEdge(g, 3, 4, 1);
    g->addEdge(g, 1, 3, 1);
    g->printGraph(g);
    
    printf("edge [0--1]:%lf\n", g->edgeCost(g, 0, 1));
    g->removeEdge(g, 0, 1);
    printf("edge [0--1]:%lf\n", g->edgeCost(g, 0, 1));

        
    del_Graph(g);
    
    return 0;
}

