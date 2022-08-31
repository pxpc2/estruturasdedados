#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int V, R, E, max, cnt;
char c1[31], c2[31];

char animals[5000][31];

struct node
{
    int value;
    struct node *next;
};

struct node *newNode(int i, struct node *next)
{
    struct node *x = malloc(sizeof(struct node*));
    x->value = i;
    x->next = next;
    return x;
}

void insertRelation(int v, int u, struct node *adj[])
{
    adj[v] = newNode(u, adj[v]);
    adj[u] = newNode(v, adj[u]);
    E++;
}

int getIndex(char *s)
{
    for (int j = 0; j < V; j++)
        if (strcmp(s, animals[j]) == 0)
            return j;
    return -1;
}

void dfs(int v, int u, struct node *adj[], int visited[])
{
    cnt++;
    visited[u] = 1;
    for (struct node *t = adj[u]; t != NULL; t = t->next)
        if (visited[t->value] == -1) dfs(u, t->value, adj, visited);
}

int main()
{
    while (1)
    {
        max = 0, cnt = 0;
        scanf("%d %d", &V, &R);
        if (V == 0 && R == 0)
            return 0;

        struct node *adj[V];
        int visited[V];

        E = 0;

        for (int i = 0; i < V; i++)
        {
            scanf("%s", animals[i]);
            adj[i] = NULL;
            visited[i] = -1;
        }

        for (int i = 0; i < R; i++)
        {
            scanf("%s %s", c1, c2);
            int x = getIndex(c1), y = getIndex(c2);
            insertRelation(x, y, adj);
        }

        for (int i = 0; i < V; i++)
        {
            if (visited[i] == -1)
            {
                cnt = 0;
                dfs(i, i, adj, visited);
                if (max < cnt) max = cnt;
            }
        }
        printf("%d\n", max);
    }
}