//
//  oocGAlg.c
//  oocGraph
//
//  Created by Xavier on 14-1-30.
//  Copyright (c) 2014年 Xavier Woo. All rights reserved.
//

#include "oocGraph.h"

#include "oocGAlg.h"
#include <stdlib.h>
#include <float.h>

//return the index of the minimal element in the array
int getMin(double *array, int *fliter, int num){
    int minPos = -1;
    int i;
    double minDist = DBL_MAX;
    
    for (i=0; i<num; i++) {
        if (fliter[i] == 1 && array[i] < minDist) {
            minPos = i;
            minDist =  array[i];
        }
    }
    
    return minPos;
}

//Dijkstra algorithm, the return value should be freed manually
int *Dijkstra(struct Graph *self, int idSource, int idSink){
    double *dist = NULL;
    int *previous = NULL;
    int *fliter = NULL;
    int i;
    int nodeCount = 0;
    int u, v;
    double alt = 0;
    
    struct EdgeLink *edgeLink = NULL;
    
    dist = (double *)malloc(self->nodeNum * sizeof(double));
    previous = (int *)malloc(self->nodeNum * sizeof(int));
    fliter = (int *)malloc(self->nodeNum * sizeof(int));

    
    for (i=0; i<self->nodeNum; i++) {
        dist[i] = DBL_MAX;
        previous[i] = -1;
        fliter[i] = 1;
    }
    dist[idSource] = 0;
    
    
    while (nodeCount < self->nodeNum) {
        u = getMin(dist, fliter, self->nodeNum);
        
        if (u == idSink) {
            break;
        }
        fliter[u] = 0;
        nodeCount++;
        
        if (dist[u] == DBL_MAX) {
            break;
        }
        
        edgeLink = self->nodeEdgeList[u];
        
        while (edgeLink != NULL) {
            v = edgeLink->edge->sink;
            if (fliter[v] == 0) {
                edgeLink = edgeLink->next;
                continue;
            }
            alt = dist[u] + edgeLink->edge->cost;
            if (alt < dist[v]) {
                dist[v] = alt;
                previous[v] = u;
                
            }
            
            edgeLink = edgeLink->next;
        }
        
    }
    
    free(dist);
    free(fliter);
    //return dist;
    return previous;
}

int *ShortestPath(struct Graph *self, int idSource, int idSink){
    int *previous = NULL;
    int *reversePath = NULL;
    int *SP = NULL;
    int hop;
    int preNode;
    int i, j;
    
    reversePath = (int*)malloc(self->nodeNum * sizeof(int));
    
    previous = Dijkstra(self, idSource, idSink);
    
    preNode = idSink;
    hop = 0;
    
    while (previous[preNode] != -1) {
        reversePath[hop] = preNode;
        hop++;
        preNode = previous[preNode];
    }
    
    SP = (int*)malloc((hop+1) * sizeof(int));
    //SP[0] = idSource;
    
    for (i = hop, j=0; i>=0; i--, j++) {
        SP[j] = reversePath[i];
    }
    
    free(reversePath);
    free(previous);
    return SP;
}