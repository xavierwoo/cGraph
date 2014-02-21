//
//  oocGAlg.c
//  oocGraph
//
//  Created by Xavier on 14-1-30.
//  Copyright (c) 2014年 Xavier Woo. All rights reserved.
//

#include "oocGraph.h"

#include "oocGAlg.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

struct PathLink{
	int *path;
	struct PathLink *next;
};

void db_ph(int *path){
	int i;
	if (path == NULL) {
		printf("NULL\n");
		return;
	}
	for (i=1; i<=path[0]; i++) {
		printf("%d ", path[i]);
	}
	printf("\n");
}

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
        
        if (u == idSink || u < 0) {
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

int *ShortestPath(struct Graph *g, int idSource, int idSink){
    int *previous = NULL;
    int *reversePath = NULL;
    int *SP = NULL;
    int hop;
    int preNode;
    int i, j;
    
    reversePath = (int*)malloc(g->nodeNum * sizeof(int));
    
    previous = Dijkstra(g, idSource, idSink);
    
    preNode = idSink;
    hop = 0;
    
	if (previous[preNode] == -1) {
		return NULL;
	}
	
    while (previous[preNode] != -1) {
        reversePath[hop] = preNode;
        hop++;
        preNode = previous[preNode];
    }
    reversePath[hop] = preNode;
	hop++;
	
    SP = (int*)malloc((hop+1) * sizeof(int));
    SP[0] = hop;
    
    for (i = hop-1, j=1; i>=0; i--, j++) {
        SP[j] = reversePath[i];
    }
    
    free(reversePath);
    free(previous);
    return SP;
}

void FreePathList(struct PathList *pl){
	int i;
	for (i=0; i<pl->numOfPaths; i++) {
		free(pl->path[i]);
	}
	free(pl->path);
	free(pl);
}

//******************************************************************//
//      This function is written for function FindKShortestPath     //
//******************************************************************//
struct Graph *alterGraph(struct Graph *g, struct PathLink *listA, int *path, int stop){
	struct Graph *alteredGraph = NULL;
	struct PathLink *linkIter = NULL;
	int i;
	
	alteredGraph = copy_Graph(g);
	
	for (linkIter = listA; linkIter->next != NULL; linkIter = linkIter->next) {
		//for (i=1; i<path[0] && i<linkIter->path[0]; i++) {
		for (i=1; i<path[0] && i<=stop; i++) {
			if (linkIter->path[i] == path[i]) {
				alteredGraph->removeEdge(alteredGraph, linkIter->path[i], linkIter->path[i+1]);
			}
			else {
				break;
			}
		}
	}
	
	
	//for (i=1; i<path[0]; i++) {
		//alteredGraph->removeEdge(alteredGraph, path[i], path[i+1]);
	//}
	
	return alteredGraph;
}

//******************************************************************//
//      This function is written for function FindKShortestPath     //
//******************************************************************//
int *getRootPAndRemoveEdges(struct Graph *g, int len, int *currP){
	int *rootP = NULL;
	int i;
	
	rootP = (int *)malloc((len + 1) * sizeof(int));
	rootP[0] = 0;
	
	for (i=1; i<len; i++) {
		rootP[i] = currP[i];
		rootP[0]++;
		g->removeNode(g, currP[i]);
	}
	g->removeEdge(g, currP[i], currP[i+1]);
	return rootP;
}

//******************************************************************//
//      This function is written for function FindKShortestPath     //
//******************************************************************//
int *mergePaths(int *root, int *sub) {
	int *merged = NULL;
	int i;
	
	merged = (int *)malloc((root[0] + sub[0] + 1) * sizeof(int));
	merged[0] = root[0] + sub[0];
	for (i=1; i<=root[0]; i++) {
		merged[i] = root[i];
	}
	for (i=1; i<=sub[0]; i++) {
		merged[root[0] + i] = sub[i];
	}
	
	return merged;
}

//******************************************************************//
//      This function is written for function addToPathLinkList     //
//******************************************************************//
double pathLength(struct Graph *g, int *path) {
	double length = 0;
	int i;
	
	for (i=1; i<path[0]; i++) {
		length += g->edgeCost(g, path[i], path[i+1]);
	}
	
	return length;
}

//******************************************************************//
//      This function is written for function FindKShortestPath     //
//******************************************************************//
struct PathLink *addToPathLinkList(struct Graph *g, struct PathLink *list, int *path){
	struct PathLink *newLink = NULL;
	struct PathLink *linkIter = NULL;
	struct PathLink *preLink = NULL;
	int FLAG_insert = 0;
	newLink = (struct PathLink *)malloc(sizeof(struct PathLink));
	
	newLink->path = path;
	newLink->next = NULL;
	
	if (list == NULL) {
		list = newLink;
		newLink->next = NULL;
	}
	else {
		for (linkIter = list, preLink = list;
			linkIter != NULL;
			preLink = linkIter, linkIter = linkIter->next) {
			
			//if (path[0] <= linkIter->path[0]) {
			if(pathLength(g, path) <= pathLength(g, linkIter->path)) {
				if (linkIter != preLink) {
					preLink->next = newLink;
					newLink->next = linkIter;
				}
				else {
					list = newLink;
					newLink->next = linkIter;
				}
				FLAG_insert = 1;
				break;
			}
			
			if (FLAG_insert == 0) {
				preLink->next = newLink;
			}
		}
	}
	
	return list;
}

//******************************************************************//
//      This function is written for function FindKShortestPath     //
//******************************************************************//
struct PathList *pathLinkToPathList(struct PathLink *list, int numOfPaths){
	struct PathList *PL = NULL;
	struct PathLink *linkIter = NULL;
	int i;
	PL = (struct PathList*)malloc(sizeof(struct PathList));
	
	PL->numOfPaths = numOfPaths;
	PL->path = (int **)malloc(numOfPaths * sizeof(int *));
	
	for (linkIter = list, i=0; linkIter != NULL; linkIter = linkIter->next, i++) {
		PL->path[i] = linkIter->path;
	}
	
	return PL;
}

//******************************************************************//
//      This function is written for function FindKShortestPath     //
//******************************************************************//
void freePathLinkList(struct PathLink *list, int freePath){
	struct PathLink *linkIter = NULL;
	struct PathLink *preLink = NULL;
	
	linkIter = list;
	
	while (linkIter != NULL) {
		preLink = linkIter;
		linkIter = linkIter->next;
		
		if (freePath != 0) {
			free(preLink->path);
		}
		free(preLink);
	}
}

struct PathList *FindKShortestPath(struct Graph *g, int idSource, int idSink, int K){
	struct PathList *PL = NULL;
	struct PathLink *listA = NULL;
	struct PathLink *listA_end = NULL;
	struct PathLink *listB = NULL;
	struct PathLink *linkIter = NULL;
	struct Graph *tmpG = NULL;
	struct Graph *tmpG2 = NULL;
	int *newPath = NULL;
	int *currP = NULL;
	int *rootP = NULL;
	int *subP = NULL;
	int NumOfFoundPath = 0;
	int iterNode;
	
	newPath = ShortestPath(g, idSource, idSink);
	
	if (newPath == NULL) {
		return NULL;
	}
	
	listA = (struct PathLink *)malloc(sizeof(struct PathLink));
	listA->path = newPath;
	listA->next = NULL;
	listA_end = listA;
	NumOfFoundPath = 1;
	
	while (NumOfFoundPath < K) {
		currP = listA_end->path;
		
		//Alter the graph based on listA
		//tmpG = alterGraph(g, listA, currP);
		tmpG = copy_Graph(g);
		for (iterNode=1; iterNode<currP[0]; iterNode++) {
			//tmpG2 = copy_Graph(tmpG);
			
			//tmpG = alterGraph(g, listA, currP, iterNode);
			tmpG = alterGraph(tmpG, listA, currP, iterNode);
			
			if (rootP != NULL ) {
				free(rootP);
			}
			//rootP = getRootPAndRemoveNodes(tmpG2, iterNode, currP);
			rootP = getRootPAndRemoveEdges(tmpG, iterNode, currP);
			
			if (subP != NULL) {
				free(subP);
			}
			//subP = ShortestPath(tmpG2, currP[iterNode], idSink);
			subP = ShortestPath(tmpG, currP[iterNode], idSink);
			
			if (subP != NULL) {
				newPath = mergePaths(rootP, subP);
				listB = addToPathLinkList(g, listB, newPath);
			}
		}
		
		if (listB == NULL) {
			//del_Graph(tmpG);
			//del_Graph(tmpG2);
			//tmpG = NULL;
			//tmpG2 = NULL;
			break;
		}
		else {//Add the shortest path in listB to listA
			listA_end->next = listB;
			listB = listB->next;
			listA_end = listA_end->next;
			listA_end->next = NULL;
			NumOfFoundPath++;
		}
		
		if (tmpG != NULL) {
			del_Graph(tmpG);
			tmpG = NULL;
		}
		if (tmpG2 != NULL) {
			del_Graph(tmpG2);
			tmpG2 = NULL;
		}
	}
	
	PL = pathLinkToPathList(listA, NumOfFoundPath);
	freePathLinkList(listA, 0);
	freePathLinkList(listB, 1);
	return PL;
}