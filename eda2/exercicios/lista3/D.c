#include <stdio.h>
#include <stdlib.h>

int busca_binaria(int *v, int len, int o);

int N, M, k;

int main()
{

    scanf("%d%d", &N, &M);
    int v[N], a[M];

    for (int i = 0; i < N; i++)
        scanf("%d", &v[i]);

    for (int i = 0; i < M; i++)
    {
        scanf("%d", &a[i]);
        printf("%d\n", busca_binaria(v, N, a[i]));
    }
    
    return 0;
}

int busca_binaria(int *v, int len, int o)
{
    int meio;
    int inicio = 0, fim = len-1;

    if (o > v[len-1]) return len;
    else if (o < v[0]) return 0;

    while (inicio < fim)
    {
        meio = (inicio + fim) / 2;
        if (v[meio] == o)
            return meio;
        else if (v[meio] < o)
            inicio = meio + 1;
        else
            fim = meio;
    }

    return inicio;
}