#include <stdio.h>
#include <stdlib.h>

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
int getMax(Heap *heap);
int heap_isEmpty(Heap *heap);

Heap *hp;
int *tmp;
int o, pl, n;

int main()
{
    hp = malloc(sizeof(Heap));
    tmp = malloc(sizeof(int) * 102);
    heap_init(hp, 102);
    while (scanf("%d", &o) != EOF)
    {
        if (o == 1)
        {
            scanf("%d", &pl);
            if (hp->size <= 100)
                heap_insert(hp, pl);
            else
            {
                if (getMax(hp) < pl)
                    continue;
                heap_insert(hp, pl);
                heap_poll(hp);
            }
        }
        else if (o == 2)
        {
            scanf("%d", &n);
            int c = 0;
            while (!heap_isEmpty(hp))
            {
                Item k = heap_poll(hp);
                tmp[c++] = k;
            }
            for (int i = c-1; i >= 0; i--)
            {
                if (i > (c-n) && i <= (c-1))
                    printf("%d ", tmp[i]);
                if (i == (c-n)) printf("%d\n", tmp[i]);
                heap_insert(hp, tmp[i]);
            }
        }
    }
}

int heap_isEmpty(Heap *heap)
{
    return (heap->size == 0);
}

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
    Item top = heap->pq[1];
    exch(heap->pq[1], heap->pq[heap->size]);
    --heap->size;
    sink(heap->pq, 1, heap->size);
    return top;
}

int getMax(Heap *heap)
{
    return heap->pq[1];
}