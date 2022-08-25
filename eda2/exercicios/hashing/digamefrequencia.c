#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char valor;
    int qtd;
} Letra;

#define key(x) (x.qtd)
#define less(x, y) {if (key(x) == key(y)) {(x.valor < y.valor)} \
else {key(x) < key(y)} }

static char curr;
static Letra *table;

void init();
void resolveLinha();

int main()
{
    init();
    while (scanf("%c", &curr) != EOF)
    {
        if (curr == '\n')
        {
            resolveLinha();
            memset(table, -1, sizeof(Letra)*128);
        }
        else
        {
            table[curr].valor = curr;
            table[curr].qtd++;
        }
    }
    return 0;
}

void init()
{
    table = malloc(sizeof(Letra) * 128);
    memset(table, -1, sizeof(Letra)*128);
}

void resolveLinha()
{
    // mergesort(table, 0, 127)
    int i = 0;
    while (table[i].qtd == 0) i++;
    while (i < 128)
    {
        printf("%hd %d\n", table[i].valor, table[i].qtd);
        i++;
    }
    printf("\n");
}

