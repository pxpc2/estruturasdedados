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

edge EDGE(int v, int w)
{
    edge e;
    e.src = v, e.dest = w;
    return e;
}

link newNode(int v, link next)
{
    link x = malloc(sizeof(link));
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
    g->adj[v] = newNode(w, g->adj[v]);
    g->adj[w] = newNode(v, g->adj[w]);
    g->E++;
}

int totalEdges(edge a[])
{
    int E = 0;
    link t;
    for (int i = 0; i < g->V; i++)
        for (t = g->adj[i]; t != NULL; t = t->next)
            if (i < t->v) a[E++] = EDGE(i, t->v);
    return E;
}