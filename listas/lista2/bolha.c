#include "stdio.h"

int _main() {
    int N, size = 0;
    int v[1000];

    while (scanf("%d", &N) != EOF)
        v[++size] = N;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (v[j + 1] < v[j]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < size; i++)
        printf("%d ", v[i]);
    printf("\n");

    return 0;
}