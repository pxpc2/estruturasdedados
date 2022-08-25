#include "stdio.h"
#include "stdlib.h"

#define key(A) (A.key)
#define less(A, B) ( key(A) < key(B) )
#define cmpexch(A, B) { if (less(B,A)) exch(A, B) }

typedef struct
{
    int key;
    int inside_heap; // flag se já foi inserida na heap de indices
} Item;

typedef struct
{
    int *pq; // guarda o indice no vetor de dados (data)
    int *qp; // guarda o índice da fila (pq)
    // i.e:        pq[ qp[x] ] = x
    //             qp[ pq[x] ] = x
    int N;
} PQHeap;



            // consideramos que já temos os dados (input)
Item *data; // e estes podem ser inseridos na PQ p/ manusear como heap
            // guardando somente os índices que apontam (tipo um ponteiro mesmo)


/**
 * @todo
 */
void swim(Item *v, PQHeap *pq, int k);
void exch_index(PQHeap *pq, int i, int j);

void pq_init(PQHeap *pq, int max)
{
    pq->N = 0;
    pq->pq = malloc(sizeof(int) * max + 1);
    pq->qp = malloc(sizeof(int) * max + 1);
}

/**
 * @param pq heap que vai armazenar o indice k de um
 * elemento específico e = data[k]
 * @param k índice
 */
void pq_insert(PQHeap *pq, int k)
{
    int n = ++pq->N;
    pq->pq[n] = k;
    pq->qp[k] = n;
    swim(data, pq, n);
}

/**
 * exch um indice i com um indice j, tanto em pq quanto em qp
 * mantendo assim a proposição pq[qp[x]] = x e vice-versa
 */
void exch_index(PQHeap *pq, int i, int j)
{
    int tmp = pq->qp[i];
    pq->qp[i] = pq->qp[j];
    pq->qp[j] = tmp;
    pq->pq[pq->qp[i]] = i;
    pq->pq[pq->qp[j]] = j;
}

void swim(Item *v, PQHeap *pq, int k)
{
    while (k > 1 && less(v[k/2], v[k]))
    {
        exch_index(pq, pq->pq[k], pq->pq[k/2]); // exch de índices
        // nao precisa fazer exch no vetor v (data)
        k /= 2;
    }
}
void sink(Item *v, PQHeap *pq, int k, int n)
{
    while (2 * k <= n)
    {
        int j = 2*k;
        if (j < n && less(v[j], v[j+1]))
            j++;
        if (!less(v[k], v[j]))
            break; // não precisa fazer a troca
        exch_index(pq, pq->pq[k], pq->pq[j]);
        k = j;
    }
}

int pq_delmax(PQHeap *pq)
{
    int n = pq->N;
    exch_index(pq, pq->pq[1], pq->pq[n]);
    sink(data, pq, 1, n-1);
    return pq->pq[pq->N--];
}

