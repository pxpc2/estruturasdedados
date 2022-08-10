#include <stdio.h>
#include <stdlib.h>

typedef int Item;
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { Item temp = A; (A) = B; (B) = temp; }
#define cmpexch(A, B) { if (less(B,A)) exch(A, B) }

Item *pls, *q, *res;
int op, qt, pl, N, size = 0;

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

void initPQ(int max_N)
{
    q = malloc(sizeof(Item) * (max_N + 1));
    N = 0;
}

int getMax()
{
    return q[1];
}

int isEmpty()
{
    return (N == 0);
}

void insert(Item v)
{
    q[++N] = v;
    swim(q, N);
}

Item removeMax()
{   // max item é o no índice 1, paizão
    exch(q[1], q[N]); // joga o max pra última pos

    int heap_length = (N - 1); // N-1 já contando com a remoção do max
    sink(q, 1, heap_length);

    /*
     vale lembrar que a length é sempre intervalo fechado
     porém como não trabalhamos com índice 0, a heap com N elementos
     já seria length "N" no intervalo fechado.
     porém, o vetor *pq tem size N+1
    */

    return q[N--]; // qm ficou em pq[N], e em seguida decrementa N
}

int main()
{
    pls = malloc(sizeof(Item) * 1000000);
    while(scanf("%d", &op) != EOF)
    {
        if (op == 1)
        {
            scanf("%d", &pl);
            pls[size] = pl;
            size++;
        }
        else if (op == 2)
        {
            scanf("%d", &qt);
            initPQ(qt+1);
            for (int i = 0; i < qt; i++)
                insert(pls[i]);
            for (int i = qt; i < size; i++)
            {
                insert(pls[i]);
                removeMax();
            }
            res = malloc(sizeof(Item) * qt);
            int z = 0;
            while (!isEmpty())
            {
                res[z] = removeMax();
                z++;
            }
            free(q);
            for (int i = z-1; i > 0; i--)
                printf("%d ", res[i]);
            printf("%d\n", res[0]);
        }
    }

    return 0;
}