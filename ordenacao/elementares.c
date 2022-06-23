typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item temp = A; (A) = B; (B) = temp;}
// #define cmpexch(A, B) {if (less(B,A) exch(A, B);)}

void selectionSort(Item* v, int l, int r);

void selectionSort(Item* v, int l, int r) {
    if (l == r) return;
    int min = l;

    for (int i = l+1; i <= r; i++)
        if (less(v[i], v[min])) min = i;

    exch(v[min], v[l])
    selectionSort(v, l+1, r);
}