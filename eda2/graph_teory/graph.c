#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct node *link; // representa já um ponteiro de node

struct node
{
    int v;
    link next;
};

struct graph
{
    int V, E;
    link *adj;
};

struct edge
{
    int src, dest;
};

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
    int src = e.src, dest = e.dest;
    g->adj[src] = newNode(dest, g->adj[src]);
    g->adj[dest] = newNode(src, g->adj[dest]);
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

void showGraph()
{
    int V = g->V, E = g->E;
    printf("Graph with %d vertices and %d edges\n", V, E);
    for (int i = 0; i < V; i++)// O(V)
    {
        printf("%2d:", i);
        for (link t = g->adj[i]; t != NULL; t = t->next)// O(V+E)
            printf(" %2d", t->v);
        printf("\n");
    }
}