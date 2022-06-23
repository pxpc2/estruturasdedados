#include "stdlib.h"
#include "stdio.h"
#include "ordenacao/elementares.c"

int main() {

    Item v[50];
    for (int i = 0; i < 50; i++) {
        v[i] = rand() % 500;
        printf("%d\n", v[i]);
    }

    selectionSort(v, 0, 49);
    printf("\n\nVETOR FOI ORDERNADO\n\n");

    for (int i = 0; i < 50; i++)
        printf("%d\n", v[i]);

    return 0;
}