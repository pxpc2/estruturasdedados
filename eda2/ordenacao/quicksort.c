#include <stdio.h>
#include <stdlib.h>
#include "eda2/ordenacao/elementares.c"

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item temp = A; (A) = B; (B) = temp;}
#define cmpexch(A, B) {if (less(B,A)) exch(A, B)}

int separa(Item *v, int l, int r);
void quickSort_ingenuo(Item *v, int l, int r);
void quickSort_mediana(Item *v, int l, int r);
void sort(Item *v, int l, int r);

// lembrar que é sempre intervalo fechado, i.e,
// l e r fazem parte do vetor (tamanho 6 ent r=5)

int separa(Item *v, int l, int r)
{
    Item piv = v[r];
    int j = l;
    for (int k = l; k < r; k++)
    {
        if (less(v[k], piv))
        {
            // deixando todos menores q o pivot a sua esquerda
            exch(v[k], v[j]);
            j++;
        }
    }
    exch(v[j], v[r]);
    return j; // nova pos do pivot
}

void quickSort_ingenuo(Item *v, int l, int r)
{
    int j;
    if (r <= l) return;
    j = separa(v, l, r);
    quickSort(v, l, j-1);
    quickSort(v, j+1, r);
}

void quickSort_mediana(Item *v, int l, int r)
{
    int j;
    if (r <= l) return;

    int m = (l+r) / 2;

    // essa condicao so deve ser usada se for utilizar o insertionSort após
    // se nao for, entao a condicao p/ return é r <= l
    if (r - l <= 32) // deixo os ultimos 32 para o insertionSort
        return; 

    cmpexch(v[m], v[r]);
    cmpexch(v[l], v[m]);
    cmpexch(v[r], v[m]);

    j = separa(v, l+1, r-1);

    quickSort(v, l, j-1);
    quickSort(v, j+1, r);
}

void sort(Item *v, int l, int r)
{
    quickSort_mediana(v, l, r);
    insertionSort(v, l, r); // já estará bem prox de ordenado
}