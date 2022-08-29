#ifndef ESTRUTURASDEDADOS_GRAPH_H
#define ESTRUTURASDEDADOS_GRAPH_H

struct node;
typedef struct node *link;
typedef struct graph graph;
typedef struct edge edge;
link newNode(int v, link next);
void initGraph(int N);
void insertEdge(edge e);
int totalEdges(edge *a);
void showGraph();

#endif //ESTRUTURASDEDADOS_GRAPH_H
