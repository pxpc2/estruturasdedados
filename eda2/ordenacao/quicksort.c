#include <stdio.h>
#include <stdlib.h>

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item temp = A; (A) = B; (B) = temp;}
#define cmpexch(A, B) {if (less(B,A)) exch(A, B)}

int separa(Item *v, int l, int r);
void quickSort(Item *v, int l, int r);

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

void quickSort(Item *v, int l, int r)
{
    int j;
    if (r <= l) return;
    j = separa(v, l, r);
    quickSort(v, l, j-1);
    quickSort(v, j+1, r);
}