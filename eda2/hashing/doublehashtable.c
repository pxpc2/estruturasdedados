#include <stdio.h>
#include <stdlib.h>

typedef struct Item
{
    int chave;
} Item;

Item NULL_ITEM = {-1};

#define key(x) (x.chave)
#define less(a,b) (key(a) < key(b))
#define hash(v, m) (v % m)
#define hash2(v, m) (v % (97*m))
#define null(A) (key(table[A]) == key(NULL_ITEM))

static int N, M;
static Item *table;

void dht_init(int max);
void dht_insert(Item x);
Item dht_search(int v);
void dht_expand();
int dht_size() {return N;}
int dht_max() {return M;}

void dht_init(int max)
{
    N = 0, M = 2*max;
    table = malloc(sizeof(Item) * M);
    for (int i = 0; i < M; i++)
        table[i] = NULL_ITEM;
}

void dht_insert(Item x)
{
    int v = key(x), i = hash(v, M), k = hash2(v, M);
    while (!null(i)) i = (i + k) % M;
    table[i] = x;
    N++;
    if (N >= M/2)
        dht_expand();
}

Item dht_search(int v)
{
    int i = hash(v, M), k = hash2(v, M);
    while (!null(i))
    {
        if (v == key(table[i]))
            return table[i];
        else i = (i + k) % M;
    }
    return NULL_ITEM;
}

void dht_expand()
{
    Item *tmp_table = table;
    int init_max = dht_max();
    M = init_max * 2; // dobra o tamanho
    dht_init(M); // init com novo max
    // agora re-inserir os elementos não nulos
    for (int i = 0; i < init_max; i++)
        if (key(tmp_table[i]) != key(NULL_ITEM))
            dht_insert(tmp_table[i]);
    free(tmp_table);
}