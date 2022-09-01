#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *next;
};

typedef struct
{
    int joao_esta;
    int menor_node;
    int tamanho;
} componente;

int V, E, J, x, y, max=0, cnt=0, min=5001, flag=-1;
int q=0;

struct node *newNode(int value, struct node *next)
{
    struct node *n = malloc(sizeof(struct node*));
    n->value = value;
    n->next = next;
    return n;
}

void insertEdge(int u, int v, struct node *adj[])
{
    adj[u] = newNode(v, adj[u]);
    adj[v] = newNode(u, adj[v]);
    E++;
}

void dfs(int u, int v, struct node *adj[], int visited[])
{
    cnt++;
    visited[v] = 1;
    if (v == J) { flag=1;}
    if (v < min) min = v;
    struct node *n;
    for (n = adj[v]; n != NULL; n = n->next)
        if (visited[n->value] == -1)
            dfs(v, n->value, adj, visited);
}

componente newComp(int joaoesta, int menor, int tam)
{
    componente c;
    c.tamanho=tam;
    c.joao_esta=joaoesta;
    c.menor_node=menor;
    return c;
}

void resetVars()
{
    cnt = 0;
    min = 5001;
    flag = -1;
}

int main()
{
    E = 0;
    scanf("%d %d", &V, &J);

    struct node *adj[V];
    int visited[V];
    componente conexas[V];

    for (int i = 0; i < V; i++)
    {
        visited[i] = -1;
        adj[i] = NULL;
        conexas[i].tamanho = -1;
    }

    while (scanf("%d %d", &x, &y) != EOF)
        insertEdge(x, y, adj);

    for (int i = 0; i < V; i++)
    {
        if (visited[i] == -1)
        {
            resetVars();
            dfs(i, i, adj, visited);
            conexas[q++] = newComp(flag, min, cnt);
        }
    }
    componente chosen;
    chosen.tamanho = -1;

    for (int i = 0; i < q; i++)
    {
        componente tmp = conexas[i];
        if ((tmp.tamanho > chosen.tamanho) ||
                ((tmp.tamanho == chosen.tamanho) && (tmp.joao_esta == 1)))
        {
            chosen.tamanho = tmp.tamanho;
            chosen.menor_node = tmp.menor_node;
            chosen.joao_esta = tmp.joao_esta;
        }

    }

    if (chosen.joao_esta == 1)
    {
        if (chosen.tamanho > 1) printf("Bora pra estrada\n");
        else if (chosen.tamanho == 1) printf("Fique em casa\n");
    }
    else
        printf("Vamos para %d\n", chosen.menor_node);


    return 0;
}