//
//  oocGraph.h
//  oocGraph
//
//  Created by Xavier on 14-1-23.
//  Copyright (c) 2014年 Xavier Woo. All rights reserved.
//

#ifndef oocGraph_h
#define oocGraph_h


struct Node{
    int ID;
    char *nodeName;
};

struct Edge{
    int source;
    int sink;
    double cost;
};

struct EdgeLink{
    struct Edge *edge;
    struct EdgeLink *next;
};

struct Graph{
    struct Node *nodeSet;
    int nodeNum;
    int nodeSetCapacity;
    struct EdgeLink *edgeSet;
    struct EdgeLink **nodeEdgeList;
    
    
    //add a node to the graph
    int (*addNode)(struct Graph *self, char *nodeName);
    
    //remove a node to the graph
    void (*removeNode)(struct Graph *self, int nodeID);
    
    //add a directed edge from idSource to idSink
    struct Edge* (*addEdge)(struct Graph *self, int idSource, int idSink, double cost);
    
    //remove a directed edge from idSource to idSink
    void (*removeEdge)(struct Graph *self, int idSource, int idSink);
    
    //print all the edges
    void (*printGraph)(struct Graph *self);
    
    //get the cost of edge from idSource to idSink
    //return 0 if no such edge
    double  (*edgeCost)(struct Graph *self, int idSource, int idSink);
};



struct Graph *Graph(struct Graph *self);
struct Graph *copy_Graph(struct Graph *self);
void del_Graph(struct Graph *self);


#endif
