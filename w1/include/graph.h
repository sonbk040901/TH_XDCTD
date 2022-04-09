#ifndef _GRAPH_H
#define _GRAPH_H
#include <stdio.h>
#include "dllist.h"
#include "jrb.h"
#include "jval.h"
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#define INFINITIVE_VALUE 10000000
#define TRUE 1
#define FALSE 0
typedef struct _graphics
{
    JRB edges;
    JRB vertices;
    JRB id;
} * Graph;
Graph createGraph();
int addVertex(Graph, int, char *);
char *getVertex(Graph, int);
void addEdge(Graph, int, int, double);
int hasEdge(Graph, int, int);
double getEdgeValue(Graph, int, int);
int indegree(Graph, int, int *);
int outdegree(Graph, int, int *);
int DAG(Graph);
void dropGraph(Graph);
void setParent(int, int, int *);
double shortestPath(Graph, int, int, int *, int *);
int getId(Graph, char *);
int hasVertex(Graph, char *);
#endif