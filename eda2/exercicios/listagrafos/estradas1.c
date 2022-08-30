#include <stdio.h>
#include <stdlib.h>

int V, E = 0;
int **adj;
int *visited;

void insertEdge(int v, int u)
{
    if (adj[v][u] == 0) E++;
    //printf("Inserting edge #%d = (%d, %d)\n", E, v, u);
    adj[v][u] = 1;
    adj[u][v] = 1;
}

void dfs(int v, int u)
{
    visited[u] = 1;
    for (int t = 0; t < V; t++)
        if (adj[u][t] != 0 && visited[t] == -1)
            dfs(u, t);
}

int main()
{
    scanf("%d", &V);

    adj = malloc(sizeof(int*) * V);
    visited = malloc(sizeof(int) * V);

    for (int i = 0; i < V; i++)
    {
        adj[i] = malloc(sizeof(int) * V);
        visited[i] = -1;
    }

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            adj[i][j] = 0;

    int v, u, conexos = 0;
    while (scanf("%d %d", &v, &u) != EOF)
    {
        insertEdge(v, u);
    }

    for (int i = 0; i < V; i++)
        if (visited[i] == -1)
        { dfs(i, i); conexos++;}

    printf("%d\n", conexos);

    return 0;
}


