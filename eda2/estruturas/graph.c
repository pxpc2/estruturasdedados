#include "stdlib.h"

typedef struct node *link; // representa já um ponteiro de node

struct node
{
    int v;
    link next;
};

typedef struct
{
    int V, E;
    link *adj;
} graph;

typedef struct
{
    int src, dest;
} edge;

graph *g;

link newLink(int v, link next)
{
    link x = malloc(sizeof(*x));
    x->v = v;
    x->next = next;
    return x;
}

void initGraph(int N)
{
    g = malloc(sizeof(*g));
    g->V = N;
    g->E = 0;
    g->adj = malloc(N * sizeof(link));
    for (int i = 0; i < N; i++)
        g->adj[i] = NULL;
}

void insertEdge(edge e)
{
    int v = e.src, w = e.dest;
    g->adj[v] = newLink(w, g->adj[v]);
    g->adj[w] = newLink(v, g->adj[w]);
    g->E++;
}