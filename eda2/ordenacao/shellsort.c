typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) {Item temp = A; (A) = B; (B) = temp;}
#define cmpexch(A, B) {if (less(B,A)) exch(A, B)}


void insertion_h(Item *v, int l, int r, int h);
void shellSort(Item *v, int l, int r);


void insertion_h(Item *v, int l, int r, int h)
{
    for (int i = l+h; i <= r; i++)
    {
        int j = i;
        Item t = *(v+j);
        while (j >= l+h && less(t, *(v + j-h)))
        {
            *(v+j) = *(v + j-h);
            j -= h;
        }
        *(v+j) = t;
    }
}

void shellSort(Item *v, int l, int r)
{
    int h;
    for (h = 1; h <= (r-l)/9; h = 3*h + 1);
    for (; h > 0; h /= 3)
        insertion_h(v, l, r, h);
}