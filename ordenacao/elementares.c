typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item temp = A; (A) = B; (B) = temp;}
#define cmpexch(A, B) {if (less(B,A)) exch(A, B)}


void selectionSort(Item* v, int l, int r);
void bubbleSort(Item *v, int l, int r);
void insertionSort(Item *v, int l, int r);
void shellSort(Item *v, int l, int r);


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
    // deixar antes ja mais organizado, com o menor ja em v[l]
    for (int i = r; i > l; i--)
        cmpexch(v[i - 1], v[i])

    // no insertionsort vamos olhando a esquerda e fazendo trocas
    for (int i = l + 2; i <= r; i++) {
        // comeca do 2o elemento pq 1o ja ta correto
        int j = i;
        Item temp = v[j]; // enquanto guarda sua posicao
        while (less(temp, v[j-1])) {
            v[j] = v[j-1];
            j--;
        }
        v[j] = temp; // insere na nova posicao correta
    }
}