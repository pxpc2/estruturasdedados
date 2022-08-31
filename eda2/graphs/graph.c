#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

static int *visited;
static int cnt;

struct node
{
    int v;
    struct node *next;
};

struct graph
{
    int V, E;
    struct node **adj;
};

struct edge
{
    int src, dest;
};

edge EDGE(int v, int w)
{
    edge e;
    e.src = v, e.dest = w;
    return e;
}

struct node *newNode(int v, struct node *next)
{
    struct node *x = malloc(sizeof(link));
    x->v = v;
    x->next = next;
    return x;
}

graph* initGraph(int N)
{
    graph *g = malloc(sizeof(*g));
    g->adj = malloc(sizeof(struct node*) * N);
    g->V = N;
    g->E = 0;

    for (int i = 0; i < N; i++)
    {
        g->adj[i] = malloc(sizeof(g->adj[i]));
        g->adj[i] = NULL;
    }
    cnt = 0;
    return g;
}

void insertEdge(graph *g, edge e)
{
    int src = e.src, dest = e.dest;
    g->adj[src] = newNode(dest, g->adj[src]);
    g->adj[dest] = newNode(src, g->adj[dest]);
    g->E++;
}

int totalEdges(graph *g, edge a[])
{
    int E = 0;
    link t;
    for (int i = 0; i < g->V; i++)
        for (t = g->adj[i]; t != NULL; t = t->next)
            if (i < t->v) a[E++] = EDGE(i, t->v);
    return E;
}

void showGraph(graph *g)
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

void dfs_recursive(graph *g, edge e)
{
    int w = e.dest;
    visited[w] = cnt++;
    for (link l = g->adj[w]; l != NULL; l = l->next)
    {
        int t = l->v;
        if (visited[t] == -1)
            dfs_recursive(g, EDGE(w, t));
    }
}

void initVisted(int V)
{
    visited = malloc(sizeof(int) * V);
    for (int i = 0; i < V; i++)
        visited[i] = -1;
    cnt = 0;
}

/**
 * @return quantidade de componentes conexos no grafo
 */
int graphSearch(graph *g)
{
    initVisted(g->V);
    int conexos = 0;
    for (int i = 0; i < g->V; i++)
    {
        if (visited[i] == -1)
        {
            dfs_recursive(g, EDGE(i, i));
            conexos++;
        }
    }
    return conexos;
}