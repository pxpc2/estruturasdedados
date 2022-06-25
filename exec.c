#include "stdio.h"
#include "ordenacao/elementares.c"

int main() {

    Item v[7] = {3, 8, 6, 5, 1, 4, 2};
    for (int i = 0; i < 7; i++)
        printf("%d\n", v[i]);
    insertionSort(v, 0, 6);
    printf("\n\nVETOR FOI ORDERNADO\n\n");

    for (int i = 0; i < 7; i++)
        printf("%d\n", v[i]);

    return 0;
}