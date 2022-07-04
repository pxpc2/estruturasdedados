#include <stdio.h>

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item temp = A; (A) = B; (B) = temp;}
#define cmpexch(A, B) {if (less(B,A)) exch(A, B)}

void bubbleSort(Item *v, int l, int r) {
    for (int i = l; i < r; i++)
        for (int j = l; j < r; j++)
        cmpexch(v[j], v[j+1])
}

int main() {
    int N, size = 0;
    int v[1000];

    while (scanf("%d", &N) != EOF) {
        v[size] = N;
        size++;
    }

    bubbleSort(v, 0, size-1);

    for (int i = 0; i < size-1; i++)
        printf("%d ", *(v+i));
    printf("%d\n", *(v + size - 1));

    return 0;
}