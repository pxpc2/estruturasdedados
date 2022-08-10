typedef int Item;
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { Item temp = A; (A) = B; (B) = temp; }
#define cmpexch(A, B) { if (less(B,A)) exch(A, B) }

static Item *pq;
static int N;

/*
 *  Implementação de uma PQ_MAX
 *  isto é, uma PQ DECRESCENTE
 */

void initPQ(int max_N)
{
    pq = malloc(sizeof(Item) * (max_N + 1));
    N = 0;
}

int isEmpty()
{
    return (N == 0);
}

void insert(Item v)
{
    pq[++N] = v;
    swim(pq, N);
}

Item removeMax()
{   // max item é o no índice 1, paizão

    exch(pq[1], pq[N]); // joga o max pra última pos

    int heap_length = N-1; // N-1 já contando com a remoção do max
    sink(pq, 1, heap_length);

    /* 
     vale lembrar que a length é sempre intervalo fechado
     porém como não trabalhamos com índice 0, a heap com N elementos
     já seria length "N" no intervalo fechado.
     porém, o vetor *pq tem size N+1 
    */

    return pq[N--]; // qm ficou em pq[N], e em seguida decrementa N
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
    while (2*k <= N)
    {
        int j = 2*k;
        if (j < N && less(pq[j], pq[j+1]))
            j++;
        if (!less(pq[k], pq[j]))
            break;
        exch(pq[k], pq[j]);
        k = j;
    }
}