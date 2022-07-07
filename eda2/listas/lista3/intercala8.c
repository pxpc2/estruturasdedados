#include <stdio.h>
#include <stdlib.h>

#define MAX 100000
#define x 8
#define less(A, B) ((A) < (B))
#define exch(A, B) {int t = A; A = B; B = t;}
#define cmpexch(A, B) {if (less(B, A)) exch(A, B)}

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

int main()
{
    int *v = (int*) malloc(sizeof(int) * (x*MAX));
    int k, z, c = 0;

    for (int i = 0; i < x; i++)
    {
        scanf("%d", &k);
        for (int j = 0; j < k; j++) 
        {
            scanf("%d", &z);
            v[c++] = z;
        }
    }

    mergeSort(v, 0, c-1);

    for (int i = 0; i < c-1; i++)
        printf("%d ", v[i]);
    printf("%d\n", v[c-1]);

    return 0;
}