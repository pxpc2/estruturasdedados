#include <stdio.h>

typedef struct Item
{
    int chave;
    long e1, e2;
    long elemento;
} Item;

// 0 de ex, mas deve ser fora das restriçoes da chave
// isto é, nao inicializado
Item NULL_ITEM = {0,0,0,0};

#define Key(x) (x.chave)
#define less(a,b) (Key(a) < Key(b))
#define hash(v, m) (v % m) // m primo
#define hash_np(v, m) ((618033 * (unsigned) v) % m)
#define null(A) (Key(table[A]) == Key(NULL_ITEM))

static int N, M;
static Item *table;

void ht_init(int max)
{
    int i;
    N = 0, M = 2 * max;
    table = malloc(sizeof(Item) * M);
    for (i = 0; i < M; i++)
        table[i] = NULL_ITEM;
}

int ht_getSize()
{
    return N;
}

void ht_insert(Item x)
{
    int v = Key(x);
    int i = hash(v, M);
    while (!null(i)) i = (i + 1) % M; // linear probing
    table[i] = x;
    N++;
}

Item ht_search(int v)
{
    int i = hash(v, M);
    while (!null(i))
        if (v == Key(table[i]))
            return table[i];
        else (i = (i+1) % M);
    return NULL_ITEM;
}