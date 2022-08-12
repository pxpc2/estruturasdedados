/*
 * Imprima os 100 menores números de um conjunto
 * de 10^6 de números
 */

#include <stdio.h>
#include <stdlib.h>

typedef int Item;
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { Item temp = A; (A) = B; (B) = temp; }
#define cmpexch(A, B) { if (less(B,A)) exch(A, B) }

void heap_init(int max_size);
void swim(int k);
void sink(int k);
void heap_insert(Item k);
Item heap_poll();
Item getMax();
void fakeMax(Item k);

Item *h;
int size, x;

int main()
{
    heap_init(102);
    for (int i = 0; i < 100; i++)
    {
        scanf("%d", &x);
        heap_insert(x);
    }
    while (scanf("%d", &x))
    {
        if (getMax() < x) continue;
        fakeMax(x);
    }
    return 0;
}

void fakeMax(Item k)
{
    h[1] = k;
    sink(size);
}

void heap_init(int max_size)
{
    h = malloc(sizeof(Item) * max_size + 1);
    size = 0;
}

void swim(int k)
{
    while (k > 1 && less(h[k/2], h[k]))
    {
        exch(h[k], h[k/2]);
        k /= 2;
    }
}

void sink(int k)
{
    while (2 * k <= size)
    {
        int j = 2*k;
        if (j < size && less(h[j], h[j+1]))
            j++;
        if (!less(h[k], h[j]))
            break;
        exch(h[k], h[j]);
        k = j;
    }
}

void heap_insert(Item k)
{
    h[++size] = k;
    swim(size);
}

Item heap_poll()
{
    Item top = h[1];
    exch(h[1], h[size]);
    --size;
    sink(1);
    return top;
}

Item getMax()
{
    return h[1];
}