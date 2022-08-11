#include "stdio.h"
#include "stdlib.h"

typedef int Item;
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )

typedef struct Heap
{
    int *pq; // armazena o índice para um Item
    int *qp; // armazena a posição na heap para tal índice (tipo uma hash)
    int size;
} Heap;

void heap_init(Heap *heap, int max_size);
int heap_isEmpty(Heap *heap);
void heap_insert(Heap *heap, int k);
void exch(Heap *h, int i, int j);
void swim(Heap *h, int k);
void sink(Heap *h, int k, int size);
Item heap_poll(Heap *heap);
void heap_change(Heap *h, int k);

void heap_init(Heap *heap, int max_size)
{
    heap = malloc(sizeof(Heap));
    heap->size = 0;
    heap->pq = malloc(sizeof(int) * max_size);
    heap->qp = malloc(sizeof(int) * max_size);
}

void swim(Heap *h, int k)
{
    while (k > 1 && less(h->pq[k/2], h->pq[k]))
    {
        exch(h, h->pq[k], h->pq[k/2]);
        k /= 2;
    }
}

void sink(Heap *h, int k, int size)
{
    while (2 * k <= size)
    {
        int j = 2*k;
        if (j < size && less(h->pq[j], h->pq[j+1]))
            j++;
        if (!less(h->pq[k], h->pq[j]))
            break; // não precisa fazer a troca
        exch(h, h->pq[k], h->pq[j]);
        k = j;
    }
}

void heap_insert(Heap *heap, int k)
{
    heap->qp[k] = ++heap->size;
    heap->pq[heap->size] = k;
    swim(heap, heap->size);
}

Item heap_poll(Heap *heap)
{
    exch(heap, heap->pq[1], heap->pq[heap->size]);
    int new_length = heap->size - 1;
    sink(heap, 1, new_length);
    return heap->pq[heap->size--];
}

void heap_change(Heap *h, int k)
{
    swim(h, h->qp[k]);
    sink(h, h->qp[k], h->size);
}

void exch(Heap *h, int i, int j)
{
    int t = h->qp[i]; h->qp[i] = h->qp[j];
    h->qp[j] = t;
    h->pq[h->qp[i]] = i;
    h->pq[h->qp[j]] = j;
}

int heap_isEmpty(Heap *heap)
{
    return heap->size == 0;
}