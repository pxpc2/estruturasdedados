typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item temp = A; (A) = B; (B) = temp;}
#define cmpexch(A, B) {if (less(B,A)) exch(A, B)}


void selectionSort(Item* v, int l, int r);
void bubbleSort(Item *v, int l, int r);
void insertionSort(Item *v, int l, int r);


void selectionSort(Item* v, int l, int r) {
    if (l == r) return;

    int min = l;
    for (int i = l+1; i <= r; i++)
        if (less(v[i], v[min])) min = i;

    exch(v[min], v[l])
    selectionSort(v, l+1, r);
}


void bubbleSort(Item *v, int l, int r) {
    for (int i = l; i < r; i++)
        for (int j = l; j < r; j++)
            cmpexch(v[j], v[j+1])
}


void insertionSort(Item *v, int l, int r) {
    for (int i = r; i > l; i--) {
        // ja deixar todo mundo mais ou menos ajeitado
        cmpexch(v[i - 1], v[i]) // e ja deixa o menor elemento no v[left]
    }
    // agr ir elemento por elemento menos o v[left]
    for (int i = l + 2; i <= r; i++) {
        int j = i;
        Item temp = v[j];
        // olhando todos a sua esquerda e trocando a posicao se for menor
        while (less(temp, v[j-1])) {
            v[j] = v[j-1];
            j--;
        }
        v[j] = temp;
    }
}