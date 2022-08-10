#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *v, int l, int r);
void merge(int *v, int l, int m, int r);
int busca_binaria(int *v, int len, int o);

int main()
{
    int N, k;
    scanf("%d", &N);

    int proibidos[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &proibidos[i]);

    mergeSort(proibidos, 0, N-1);

    while (scanf("%d", &k) != EOF)
    {
        int r = busca_binaria(proibidos, N, k);
        if (r == -1) printf("nao\n");
        else printf("sim\n");
    }

    return 0;
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
        v[i] = v2[k++];
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

int busca_binaria(int *v, int len, int o)
{
    int inicio = 0, fim = len-1;
    while (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        if (v[meio] == o)
            return meio;
        else if (v[meio] < o)
            inicio = meio + 1;
        else
            fim = meio;
    }
    return -1;
}