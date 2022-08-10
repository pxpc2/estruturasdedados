#include <stdio.h>

void selectionSort(int *v, int l, int r) {
    if (l == r) return;
    int minPos = l;

    for (int i = l+1; i <= r; i++)
        if (*(v+i) < *(v+minPos))
            minPos = i;

    int t = *(v+minPos);
    *(v+minPos) = *(v+l);
    *(v+l) = t;
    selectionSort(v, l+1, r);
}

int main() {

    int N, s = 0;
    int v[1000];

    while (scanf("%d", &N) != EOF) {
        v[s] = N;
        s++;
    }

    selectionSort(v, 0, s-1);

    for (int i = 0; i < s-1; i++)
        printf("%d ", *(v+i));
    printf("%d\n", *(v + s - 1));

    return 0;
}