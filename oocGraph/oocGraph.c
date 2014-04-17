//
//  oocGraph.c
//  oocGraph
//
//  Created by Xavier on 14-1-23.
//  Copyright (c) 2014年 Xavier Woo. All rights reserved.
//

#define INIT_NODE_CAPACITY 16

#include <stdio.h>
#include <stdlib.h>
#include "oocGraph.h"

struct Graph *copy_Graph(struct Graph *self){
    int i;
    struct Graph *cg = NULL;
    struct EdgeLink *el = NULL;
    
    cg = Graph(cg);
    
    //copy nodes
    for (i=0; i<self->nodeNum; i++) {
        Graph_addNode(cg, self->nodeSet[i].nodeName);
    }
    
    
    //copy edges
    el = self->edgeSet;
    while (el != NULL) {
        Graph_addEdge(cg, el->edge->source, el->edge->sink, el->edge->cost);
        el = el->next;
    }
    
    return cg;
}

void Graph_removeNode(struct Graph *self, int nodeID){
    int i;
    if (nodeID >= self->nodeNum || nodeID < 0 || self->nodeSet[nodeID].ID < 0) {
        return;
    }
    
    self->nodeSet[nodeID].ID = -1;
    
    //remove all the edges connected to nodeID
    for (i=0; i<self->nodeNum; i++) {
        if (Graph_edgeCost(self, i, nodeID) > 0) {
            Graph_removeEdge(self, i, nodeID);
        }
        if (Graph_edgeCost(self, nodeID, i) > 0) {
            Graph_removeEdge(self, nodeID, i);
        }

    }
}

double Graph_edgeCost(struct Graph *self, int idSource, int idSink){
    struct EdgeLink *edgeLink = NULL;
    
    if (idSource >= self->nodeNum || idSink >= self->nodeNum) {
        return 0;
    }
    
    edgeLink = self->nodeEdgeList[idSource];
    while (edgeLink != NULL) {
        if (edgeLink->edge->source == idSource && edgeLink->edge->sink == idSink) {
            return edgeLink->edge->cost;
        }
        edgeLink = edgeLink->next;
    }
    
    return 0;
}

int Graph_changeEdgeCost(struct Graph *self, int idSource, int idSink, double cost){
	struct EdgeLink *edgeLink = NULL;
	
	if (idSource >= self->nodeNum || idSink >= self->nodeNum) {
        return -1;
    }
	if (cost == 0) {
		Graph_removeEdge(self, idSource, idSink);
		return 0;
	}
	
	edgeLink = self->nodeEdgeList[idSource];
    while (edgeLink != NULL) {
        if (edgeLink->edge->source == idSource && edgeLink->edge->sink == idSink) {
			edgeLink->edge->cost = cost;
            return 0;
        }
        edgeLink = edgeLink->next;
    }
	
	return -1;
}

void Graph_removeEdge(struct Graph *self, int idSource, int idSink){
    struct EdgeLink *edgeLink = NULL;
    struct EdgeLink *preLink = NULL;
    struct Edge *edge = NULL;
    
    if (idSource >= self->nodeNum || idSink >= self->nodeNum) {
        return;
    }
    
    //remove from link list
    edgeLink = self->nodeEdgeList[idSource];
    while (edgeLink != NULL) {
        if (edgeLink->edge->source == idSource && edgeLink->edge->sink == idSink) {
            
            edge = edgeLink->edge;
            
            //remove link edgeLink
            if (preLink == NULL) {
                self->nodeEdgeList[idSource] = edgeLink->next;
            }
            else{
                preLink->next = edgeLink->next;
            }
            free(edgeLink);
            break;
        }
        preLink = edgeLink;
        edgeLink = edgeLink->next;
    }
    
    //remove from edge set
    if (edge != NULL) {
        edgeLink = self->edgeSet;
        preLink = NULL;
        while (edgeLink != NULL) {
            if (edge == edgeLink->edge) {
                
                if (preLink == NULL){
                    self->edgeSet = edgeLink->next;
                }
                else{
                    preLink->next = edgeLink->next;
                }
                
                free(edge);
                free(edgeLink);
                break;
            }
            preLink = edgeLink;
            edgeLink = edgeLink->next;
        }
        
    }
}

void Graph_printGraph(struct Graph *self){
    struct EdgeLink *edgeLink = NULL;
    
    edgeLink = self->edgeSet;
    
    printf("Graph with %d nodes:\n Edges:\n", self->nodeNum);
    while (edgeLink != NULL) {
        printf("  [%d--%d](%lf)\n", edgeLink->edge->source, edgeLink->edge->sink, edgeLink->edge->cost);
        edgeLink = edgeLink->next;
    }
}


int findVacantNodeID(struct Graph *self){
    int i;
    for (i=0; i<self->nodeNum; i++) {
        if (self->nodeSet[i].ID < 0) {
            return i;
        }
    }
    return self->nodeNum;
}

int Graph_addNode(struct Graph *self, char *nodeName){
    int vacantID;
    struct Node *newNode;
    
    //check if there is a vacant id
    vacantID = findVacantNodeID(self);
    if (vacantID < self->nodeNum) {
        self->nodeSet[vacantID].ID = vacantID;
        self->nodeSet[vacantID].nodeName = nodeName;
        return vacantID;
    }
    
    //Enlarge the nodeSet space
    if (self->nodeNum == self->nodeSetCapacity) {
        self->nodeSetCapacity *= 2;
        
        self->nodeSet = (struct Node*)realloc(self->nodeSet, self->nodeSetCapacity * sizeof(struct Node));
        self->nodeEdgeList = (struct EdgeLink**)realloc(self->nodeEdgeList, self->nodeSetCapacity * sizeof(struct EdgeLink**));
    }
    
    newNode = &self->nodeSet[self->nodeNum];
    
    newNode->ID = self->nodeNum;
    newNode->nodeName = nodeName;
    self->nodeEdgeList[self->nodeNum] = NULL;
    self->nodeNum++;
    
    return newNode->ID;
}



void del_Graph(struct Graph *self){
    int i;
    struct EdgeLink *edgeLink, *tmpLink;
    
    edgeLink = self->edgeSet;
    while (edgeLink != NULL) {
        tmpLink = edgeLink;
        edgeLink = edgeLink->next;
        free(tmpLink->edge);
        free(tmpLink);
    }
    
    for (i=0; i<self->nodeNum; i++) {
        edgeLink = self->nodeEdgeList[i];
        
        while (edgeLink != NULL) {
            tmpLink = edgeLink;
            edgeLink = edgeLink->next;
            free(tmpLink);
        }
    }
    free(self->nodeEdgeList);
    free(self->nodeSet);
    free(self);
    
}

struct Edge *newEdge(int idSource, int idSink, double cost){
    struct Edge *edge = NULL;
    edge = (struct Edge*)malloc(sizeof(struct Edge));
    
    edge->source = idSource;
    edge->sink = idSink;
    edge->cost = cost;
    
    return edge;
}

struct Edge *Graph_addEdge(struct Graph *self, int idSource, int idSink, double cost){
    struct Edge *edge = NULL;
    struct EdgeLink *edgeLinkToSet, *edgeLinkToList, *edgeLink;
    
    if (idSource >= self->nodeNum
        || idSink >= self->nodeNum
        || cost == 0
        || Graph_edgeCost(self, idSource, idSink) != 0) {
        return NULL;
    }
    
    edge = newEdge(idSource, idSink, cost);
    
    edgeLinkToSet = (struct EdgeLink*)malloc(sizeof(struct EdgeLink));
    edgeLinkToSet->edge = edge;
    edgeLinkToList = (struct EdgeLink*)malloc(sizeof(struct EdgeLink));
    edgeLinkToList->edge = edge;
    
    
    //add to edgeSet
    edgeLink = self->edgeSet;
    self->edgeSet = edgeLinkToSet;
    edgeLinkToSet->next = edgeLink;
    
    //add to node edge List
    edgeLink = self->nodeEdgeList[idSource];
    self->nodeEdgeList[idSource] = edgeLinkToList;
    edgeLinkToList->next = edgeLink;
    
    return edge;
}

struct Graph  *Graph(struct Graph *self){
    int i;
    
    self = (struct Graph*)malloc(sizeof(struct Graph));
    
    //Init nodeSet
    self->nodeNum = 0;
    self->nodeSetCapacity = INIT_NODE_CAPACITY;
    self->nodeSet = (struct Node*)malloc(INIT_NODE_CAPACITY * sizeof(struct Node));
    
    //Init nodeEdgeList
    self->nodeEdgeList = (struct EdgeLink**)malloc(INIT_NODE_CAPACITY * sizeof(struct EdgeLink*));
    for (i=0; i<INIT_NODE_CAPACITY; i++) {
        self->nodeEdgeList[i] = NULL;
    }
    
    
    self->edgeSet = NULL;
    
    
    return self;
}