#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *v, int l, int r);
void merge(int *v, int l, int m, int r);
int busca_binaria(int *v, int len, int o);

int main()
{
    int N, M, k;
    scanf("%d%d", &N, &M);
    int *v = malloc(sizeof(int) * N);
    int *e = malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++)
    {
        int p;
        scanf("%d", &p);
        v[i] = e[i] = p;
    }

    mergeSort(v, 0, N-1);

    for (int i = 0; i < M; i++)
    {
        scanf("%d", &k);
        int z = busca_binaria(v, N, k);
        if (z == -1) 
            printf("-1\n");
        else
        {
            for (int i = 0; i < N; i++)
                if (e[i] == k) printf("%d\n", i);
        }
    }
    free(v);
    free(e);
    return 0;
}

int busca_binaria(int *v, int len, int o)
{
    int meio;
    int inicio = 0, fim = len-1;

    if (o > v[len-1] || o < v[0]) return -1;

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

    return -1;
}

void merge(int *v, int l, int m, int r)
{
    int k = 0, i = l, j = m+1;
    int *v2 = (int*) malloc(sizeof(int) * (r - l + 1));
    while (i <= m && j <= r)
    {
        if (v[i] <= v[j])
            v2[k++] = v[i++];
        else 
            v2[k++] = v[j++];
    }
    while (i <= m) 
        v2[k++] = v[i++];

    while (j <= r) 
        v2[k++] = v[j++];

    k = 0;
    for (i = l; i <= r; i++)
    {
        v[i] = v2[k++];
    }
    free(v2);
}

void mergeSort(int *v, int l, int r)
{
    if (l >= r) return;
    int m = (r + l) / 2;
    mergeSort(v, l, m);
    mergeSort(v, m + 1, r); 
    merge(v, l, m, r);  
}