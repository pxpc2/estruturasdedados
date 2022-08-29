#include "stdio.h"
#include "stdlib.h"

typedef int Item;
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { Item temp = A; (A) = B; (B) = temp; }
#define cmpexch(A, B) { if (less(B,A)) exch(A, B) }

typedef struct Heap
{
    Item *pq;
    int size;
} Heap;

void heap_init(Heap *heap, int max_size);
void swim(Item *pq, int k);
void sink(Item *pq, int k, int size);
void heap_insert(Heap *heap, Item k);
Item heap_poll(Heap *heap);

void heap_init(Heap *heap, int max_size)
{
    heap->pq = malloc(sizeof(Item) * max_size + 1);
    heap->size = 0;
}

void swim(Item *pq, int k)
{
    // até chegar no topo (k=1), compara se o pai é menor que o filho
    while (k > 1 && less(pq[k/2], pq[k]))
    {
        // se pai é menor que o filho, fazer a troca
        exch(pq[k], pq[k/2]);
        k /= 2; // e checa agora na nova pos
    }
}

void sink(Item *pq, int k, int size)
{
    // até chegar no fundo
    while (2 * k <= size)
    {
        int j = 2*k;
        if (j < size && less(pq[j], pq[j+1]))
            j++;
        if (!less(pq[k], pq[j]))
            break; // não precisa fazer a troca
        exch(pq[k], pq[j]);
        k = j;
    }
}

void heap_insert(Heap *heap, Item k)
{
    heap->pq[++heap->size] = k;
    swim(heap->pq, heap->size);
}

Item heap_poll(Heap *heap)
{
    // joga o max para última pós
    exch(heap->pq[1], heap->pq[heap->size]);
    int new_length = heap->size - 1; // já contando a remoção
    sink(heap->pq, 1, new_length);
    return heap->pq[heap->size--];
}

int getMax(Heap *heap)
{
    return heap->pq[1];
}

/*int main()
{
    Heap *h = malloc(sizeof(Heap));
    heap_init(h, 8);

    heap_insert(h, 2);
    heap_insert(h, 5);
    heap_insert(h, 8);
    heap_insert(h, 7);
    heap_insert(h, 1);
    heap_insert(h, 0);
    heap_insert(h, 9);
    heap_insert(h, 2);

    Item r = heap_poll(h);
    printf("removed: %d\n", r);

    Item r2 = heap_poll(h);
    printf("new removed: %d\n", r2);

    Item r3 = heap_poll(h);
    printf("new removed: %d\n", r3);
    Item r4 = heap_poll(h);
    printf("new removed: %d\n", r4);
    Item r5 = heap_poll(h);
    printf("new removed: %d\n", r5);

    for (int i = 1; i <= h->size; i++)
        printf("element %d = %d\n", i, h->pq[i]);

}*/