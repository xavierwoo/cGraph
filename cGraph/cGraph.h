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
};



struct Graph *Graph(struct Graph *self);
struct Graph *copy_Graph(struct Graph *self);
void del_Graph(struct Graph *self);

int Graph_addNode(struct Graph *self, char *nodeName);
void Graph_removeNode(struct Graph *self, int nodeID);
double Graph_edgeCost(struct Graph *self, int idSource, int idSink);
int Graph_changeEdgeCost(struct Graph *self, int idSource, int idSink, double cost);
void Graph_removeEdge(struct Graph *self, int idSource, int idSink);
struct Edge *Graph_addEdge(struct Graph *self, int idSource, int idSink, double cost);
void Graph_printGraph(struct Graph *self);




#endif
