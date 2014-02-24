//
//  oocGAlg.h
//  oocGraph
//
//  Created by Xavier on 14-1-30.
//  Copyright (c) 2014年 Xavier Woo. All rights reserved.
//

#ifndef oocGAlg_h
#define oocGAlg_h

struct Graph;

struct PathList{
	int numOfPaths;
	int **path;
};

//****************************************************************************************//
//    Find the shortest path from node idSource to node idSink using Dijkstra algorithm   //
//                                                                                        //
//  The format of the returned array is:                                                  //
//    {[number of nodes], [idSource], [intermediate node1], ..., [idSink]}                //
//                                                                                        //
//  The array should be freed manually to avoid memory leaking!                           //
//****************************************************************************************//
int *ShortestPath(struct Graph *self, int idSource, int idSink);


//*****************************************************************************************//
//                              The Dijkstra algorithm                                     //
//                                                                                         //
//  If assign -1 to idSink, the algorithm will find the shortest paths from idSource to all//
//the other nodes.                                                                         //
//                                                                                         //
//  The returned array should be freed manually to avoid memory leaking!                   //
//*****************************************************************************************//
int *Dijkstra(struct Graph *self, int idSource, int idSink);

//*****************************************************************************************//
//                        Free the memory that a PathList uses                             //
//*****************************************************************************************//
void FreePathList(struct PathList *pl);

struct PathList *FindKShortestPath(struct Graph *g, int idSource, int idSink, int K);
#endif
