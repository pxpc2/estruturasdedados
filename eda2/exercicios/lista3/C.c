#include <stdio.h>
#include <stdlib.h>

// l,m e r sao indices, comeco meio e fim (INCLUSIVO)
void merge(int *v, int l, int m, int r)
{
    // indices para cada vetor
    // vetor novo, primeira metade e segunda metade
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
    mergeSort(v, l, m); // inicio até meio
    mergeSort(v, m + 1, r); // meio+1 até fim
    merge(v, l, m, r);  // junta tudo
}

int main()
{
    int k, N = 0;
    int v[100000];

    while (scanf("%d", &N) != EOF) 
        v[k++] = N;

    mergeSort(v, 0, k-1);

    for (int i = 0; i < k-1; i++)
        printf("%d ", v[i]);
    printf("%d\n", v[k-1]);

    return 0;
}