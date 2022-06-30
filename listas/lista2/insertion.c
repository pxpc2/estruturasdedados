#include <stdio.h>

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {int t = A; A = B; B = t;}
#define cmpexch(A, B) {if (less(B, A)) exch(A, B)}

int main() {

    int N, size = 0;
    int v[1000];

    while (scanf("%d", &N) != EOF) {
        v[size] = N;
        size++;
    }

    for (int i = size-1; i > 0; i--)
    cmpexch(*(v + i - 1), *(v + i));

    for (int i = 0 + 2; i <= size-1; i++) {
        int j = i;
        int temp = *(v+j);
        while (less(temp, *(v + j - 1))) {
            *(v+j) = *(v+j-1);
            j--;
        }
        *(v+j) = temp;
    }

    for (int i = 0; i < size-1; i++)
        printf("%d ", *(v+i));
    printf("%d\n", *(v + size - 1));

    return 0;
}