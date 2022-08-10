#include <stdio.h>
#include <stdlib.h>

void mergeSort(int *v, int l, int r);
void merge(int *v, int l, int m, int r);

int main()
{
    int N;
    scanf("%d", &N);

    int v[N];

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &v[i]);
    }

    mergeSort(v, 0, N-1);

    for (int i = 0; i < N; i++)
    {
        printf("%d, ", v[i]);
    }

    return 0;
}

void merge(int *v, int l, int m, int r)
{
    int k = 0, i = l, j = m+1;
    int *v2 = (int*) malloc(sizeof(int) * (r - l + 1));
    while (i <= m && j <= r)
    {

        if (v[i] == v[j])
        {
            printf("%d repetido\n", v[i]);
            v2[k++] = v[i++];
            ++j;
        }
        else if (v[i] < v[j])
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