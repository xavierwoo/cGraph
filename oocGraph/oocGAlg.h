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


//****************************************************************************************//
//The return value of the functions below should be freed maually to avoid memory leaking!//
//****************************************************************************************//

int *Dijkstra(struct Graph *self, int idSource, int idSink);
int *ShortestPath(struct Graph *self, int idSource, int idSink);

#endif
