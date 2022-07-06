typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item temp = A; (A) = B; (B) = temp;}
#define cmpexch(A, B) {if (less(B,A)) exch(A, B)}

void merge(Item *v, int l, int r1, int r2);

void merge(Item *v, int l, int r1, int r2) 
{
    Item *v2 = malloc(sizeof(Item)*(r2 - l + 1));
    int k = 0; // indice contador do novo vetor, o ordenado
    int i = l, j = r1+1;

    while (i <= r1 && j <= r2)
    {
        if (less(v[i], v[j]))
            v2[k++] = v[i++];
        else
            v2[k++] = v[j++];
    }

    // agora olhar o que sobrou pra cada metade, que já eram os maiores
    while (i <= r1) v2[k++] = v[i++];
    while (r <= r2) v2[k++] = v[j++];

    k = 0;
    for (i = l; i <= r2; i++)
        v[i] = v2[k++];
}

void mergeSort(Item *v, int l, int r)
{
    if (l == r) return;
    int meio = (r+l) / 2;
    mergeSort(v, l, meio);
    mergeSort(v, meio-1, r);
    merge(v, l, meio, r); 
}