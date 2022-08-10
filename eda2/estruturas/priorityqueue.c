typedef int Item;
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { Item temp = A; (A) = B; (B) = temp; }
#define cmpexch(A, B) { if (less(B,A)) exch(A, B) }

struct PQst
{
    Item *q;
    int N;
};

/*
 *  Implementação de uma PQ_MAX
 *  isto é, uma PQ DECRESCENTE
 */

void initPQ(int max_N, struct PQst *pq)
{
    pq->q = malloc(sizeof(Item) * (max_N + 1));
    pq->N = 0;
}

int isEmpty(struct PQst *pq)
{
    return (pq->N == 0);
}

void insert(Item v, struct PQst *pq)
{
    pq->q[++pq->N] = v;
    swim(pq->q, pq->N);
}

Item removeMax(struct PQst *pq)
{   // max item é o no índice 1, paizão

    exch(pq->q[1], pq->q[pq->N]); // joga o max pra última pos

    int heap_length = (pq->N - 1); // N-1 já contando com a remoção do max
    sink(pq->q, 1, heap_length);

    /* 
     vale lembrar que a length é sempre intervalo fechado
     porém como não trabalhamos com índice 0, a heap com N elementos
     já seria length "N" no intervalo fechado.
     porém, o vetor *pq tem size N+1 
    */

    return pq->q[pq->N--]; // qm ficou em pq[N], e em seguida decrementa N
}

void swim(Item *pq, int k) // () fix_up
{
    while (k > 1 && less(pq[k/2], pq[k]))
    {
        exch(pq[k], pq[k/2]);
        k /= 2;
    }
}

void sink(Item *pq, int k, int l) // () fix_down
{
    while (2*k <= l)
    {
        int j = 2*k;
        if (j < l && less(pq[j], pq[j+1]))
            j++;
        if (!less(pq[k], pq[j]))
            break;
        exch(pq[k], pq[j]);
        k = j;
    }
}