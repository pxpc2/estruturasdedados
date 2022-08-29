#ifndef ESTRUTURASDEDADOS_GRAPH_H
#define ESTRUTURASDEDADOS_GRAPH_H

struct node;
typedef struct node *link;
typedef struct graph graph;
typedef struct edge edge;
link newNode(int v, link next);
graph* initGraph(int N);
void insertEdge(graph *g, edge e);
int totalEdges(graph *g, edge *a);
void showGraph(graph *g);
edge EDGE(int v, int w);
link *adj(graph *G);

#endif //ESTRUTURASDEDADOS_GRAPH_H
