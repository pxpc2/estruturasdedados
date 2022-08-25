#include <stdio.h>
#include <stdlib.h>

int N, K; // entre 1 e 1e5
int n;
void resolverCaso();

int main()
{
    while (1)
    {
        scanf("%d%d", &N, &K);
        if (N == 0 && K == 0) break;
        int *notas = malloc(sizeof(int) * N);
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &n);
            notas[i] = n;
        }
        resolverCaso();
    }
    return 0;
}

void resolverCaso()
{

    for (int i = 0; i < K; i++){}
        // pq_insert(i); inserir indice
    // print("%d", pq_poll());
}